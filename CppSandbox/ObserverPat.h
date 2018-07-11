#include <vector>
#include <algorithm>
#include <iostream>


namespace Observer
{

	class Subject;



	class IListener
	{
	public:
		virtual void OnSubjectUpdate(Subject* subject) = 0;
	};



	class Subject
	{
		std::vector<IListener*> m_listeners;

	public:
		void AddListener(IListener* listener)
		{
			m_listeners.push_back(listener);
		}

		void RemoveListener(IListener* listener)
		{
			m_listeners
				.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
		}

		void UpdateListeners()
		{
			for (auto listener : m_listeners)
			{
				listener->OnSubjectUpdate(this);
			}
		}
	};



	class FooSubject : public Subject
	{
		int m_someInt;
		const char* m_someText;
	public:

		FooSubject() :
			m_someInt(0),
			m_someText("")
		{

		}

		int getSomeInt() const
		{
			return m_someInt;
		}

		const char* getSomeText() const
		{
			return m_someText;
		}

		void SetValues(int someInt, const char* someText)
		{
			m_someInt = someInt;
			m_someText = someText;
			UpdateListeners();
		}
	};



	class BarListener : public IListener
	{

		void OnSubjectUpdate(Subject* subject) override
		{
			FooSubject* fooSubject = reinterpret_cast<FooSubject*>(subject);
			std::cout 
				<< "Subject updated values" 
				<< "\nSomeInt: " << fooSubject->getSomeInt() 
				<< "\nSomeText: " << fooSubject->getSomeText() 
				<< "\n";
		}

	};



	void ObserverSnippet()
	{

		FooSubject foo;
		BarListener bar;

		foo.AddListener(&bar);

		foo.SetValues(std::rand(), "some value");
				
	}

}

