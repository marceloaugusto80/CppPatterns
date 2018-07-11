#include <memory>
#include <iostream>




namespace Strategy
{


	class ICalculationBehaviour
	{
	
	public:

		virtual int Calculate(int a) = 0;


	};


	class DoubleCalculationBehaviour : public ICalculationBehaviour
	{

	public:

		int Calculate(int a) override
		{
			return a * 2;
		}
	};


	class SquareCalculationBehaviour : public ICalculationBehaviour
	{
	public:

		int Calculate(int a) override
		{
			return a * a;
		}
	};


	class Client
	{
		ICalculationBehaviour* m_calculator;

		int m_value;

	public:

		Client() :
			m_calculator(0), 
			m_value(0)
			
		{}

		void SetValue(int value)
		{
			m_value = value;
		}

		int GetValue() const
		{
			return m_value;
		}

		int GetCalculatedValue() const
		{
			if (m_calculator)
			{
				return m_calculator->Calculate(m_value);
			}

			return m_value;
		}

		void SetCalculator(ICalculationBehaviour* calculator)
		{
			m_calculator = calculator;
		}

	};



	void StrategySnippet()
	{


		auto doubleBehaviour = std::unique_ptr<DoubleCalculationBehaviour>(new DoubleCalculationBehaviour());
		auto squareBehaviour = std::unique_ptr<SquareCalculationBehaviour>(new SquareCalculationBehaviour());
		Client client;
		
		char operation;
		int num;

		std::cout << "choose value and operation:" << "\n";

		std::cin >> num >> operation;

		if (operation == 's')
		{
			std::cout << "Behaviour: Square\n";
			client.SetCalculator(squareBehaviour.get());
		}
		else
		{
			std::cout << "Behaviour: Double\n";
			client.SetCalculator(doubleBehaviour.get());
		}

		std::cout << "Value: " << num << "\n";
		client.SetValue(num);

		int result = client.GetCalculatedValue();
		std::cout << "Calculated value: " << result;

	}



}