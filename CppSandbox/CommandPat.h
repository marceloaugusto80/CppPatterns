#include <stack>
#include <memory>
#include <iostream>

namespace Command
{

	class Target
	{
		
		int m_number;
		const char* m_text;

	public:

		Target() :
			m_number(0),
			m_text("")
		{}

		void SetNumber(int n)
		{
			m_number = n;
		}

		void SetText(const char* text)
		{
			m_text = text;
		}

		const char* GetText() const
		{
			return m_text;
		}

		int GetNumber() const
		{
			return m_number;
		}

	};

	class CommandBase
	{

		Target* m_target;

	public:

		CommandBase(Target* target):
			m_target(target)
		{}

		virtual void Execute() = 0;

		virtual void Undo() = 0;

		Target * GetTarget() const
		{
			return m_target;
		}

	};

	class SumNumberCommand : public CommandBase
	{

		int m_ammountToSum;

	public:


		SumNumberCommand(Target* target, int ammoutToSum) : CommandBase(target)
		{
			m_ammountToSum = ammoutToSum;
		}

		void Execute() override
		{
			GetTarget()->SetNumber(GetTarget()->GetNumber() + m_ammountToSum);
		}

		void Undo() override
		{
			GetTarget()->SetNumber(GetTarget()->GetNumber() - m_ammountToSum);
		}

	};

	class MultiplyNumberCommand : public CommandBase
	{
		int m_amountToMultiply;

	public:

		MultiplyNumberCommand(Target* target, int ammoutToSum) : CommandBase(target)
		{
			m_amountToMultiply = ammoutToSum;
		}

		void Execute() override
		{
			GetTarget()->SetNumber(GetTarget()->GetNumber() * m_amountToMultiply);
		}

		void Undo() override
		{
			GetTarget()->SetNumber(GetTarget()->GetNumber() / m_amountToMultiply);
		}

	};

	class CommandManager
	{
		std::stack<CommandBase*> m_undoStack;
		std::stack<CommandBase*> m_redoStack;

	public:

		void Execute(CommandBase* cmd)
		{
			cmd->Execute();
			m_undoStack.push(cmd);
		}


		void Undo()
		{

			if (m_undoStack.size() < 1) return;

			CommandBase* cmd = m_undoStack.top();

			cmd->Undo();

			m_undoStack.pop();

			m_redoStack.push(cmd);
		
		}

	};



	void Snippet()
	{

		std::cout << "### Command Pattern ###\n\n";

		Target target;

		CommandManager cmdManager;

		std::shared_ptr<CommandBase> addCmd = std::make_shared<SumNumberCommand>(&target, 8);
		cmdManager.Execute(addCmd.get());
		std::cout << "adding 8. target value: " << target.GetNumber() << "\n";

		std::shared_ptr<CommandBase> multiplyCmd = std::make_shared<MultiplyNumberCommand>(&target, 2);
		cmdManager.Execute(multiplyCmd.get());
		std::cout << "multiply 2. target value: " << target.GetNumber() << "\n";

		cmdManager.Undo();
		std::cout << "undo multiply. target value: " << target.GetNumber() << "\n";

		cmdManager.Undo();
		std::cout << "undo add. target value: " << target.GetNumber();

	}




}