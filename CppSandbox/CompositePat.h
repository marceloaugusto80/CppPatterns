#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

namespace Composite
{
    static int counter = 0;

    class IComponent
    {
        static int _counter;

        public:

        virtual void DoSomething() = 0;
    };


    class Component : public IComponent
    {
        public:

        void DoSomething() override 
        {
            std::cout << "I'm component number " << counter << "\n";
			counter++;
        }
    };


    class Composite : public IComponent
    {
        std::vector<IComponent*> m_children;

        public:

        void AddComponent(IComponent* component)
        {
            m_children.push_back(component);
        }

        void RemoveComponent(IComponent* component)
        {
            m_children.erase(std::remove(m_children.begin(), m_children.end(), component), m_children.end());
        }

        void DoSomething() override
        {
            std::cout << "Im a composite with " << m_children.size() << " elements\n";
            for(auto child : m_children)
            {
                child->DoSomething();
            }
        }
    };

    
    void CompositeSnippet()
    {
		std::cout << "## Component Pattern ##\n\n";

        auto component1 = std::unique_ptr<IComponent>(new Component());
		auto component2 = std::unique_ptr<IComponent>(new Component());
        auto composite1 = std::unique_ptr<IComponent>(new Composite());
		auto composite2 = std::unique_ptr<IComponent>(new Composite());

		static_cast<Composite*>(composite1.get())->AddComponent(component1.get());
		static_cast<Composite*>(composite2.get())->AddComponent(composite1.get());
		static_cast<Composite*>(composite1.get())->AddComponent(component1.get());
		static_cast<Composite*>(composite2.get())->AddComponent(component2.get());


        component1->DoSomething();
        composite1->DoSomething();

    }

};
