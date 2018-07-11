#include <iostream>
#include <algorithm>
#include <memory>


namespace MethodTemplate
{

	class Subject
	{
		int m_value;
	
	protected:

		virtual int DoSomeCalculation(int a) = 0;

	public:

		Subject(int initialValue)
			: m_value(initialValue)
		{}

		Subject() : Subject(0)
		{}


		void CalculateNumbers()
		{
			m_value = DoSomeCalculation(m_value);
		}

		int GetValue() const
		{
			return m_value;
		}

	};



	class DoubleCalculation : public Subject
	{
	protected:

		int DoSomeCalculation(int a) override
		{
			return a * 2;
		}

	public:

		DoubleCalculation(int value) : Subject(value)
		{}
	};



	void MethodTemplateSnippet()
	{
		std::cout << "## method template ##\n\n";

		int val = std::rand();

		std::cout << "Value: " << val << "\n";

		auto subject = std::unique_ptr<Subject>(new DoubleCalculation(val));

		subject->CalculateNumbers();

		std::cout << "subject has value: " << subject->GetValue() << "\n";


	}

}