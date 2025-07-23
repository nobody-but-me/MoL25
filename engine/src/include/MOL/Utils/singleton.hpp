
#ifndef SINGLETON_H
#define SINGLETON_H

namespace Utils
{
    
    template <typename T>
    class Singleton
    {
	private:
	protected:
	    Singleton() {}
	public:
	    Singleton(const Singleton *singleton) = delete;
	    Singleton* operator = (const Singleton *) = delete;
	    
	    static T* get_instance() {
		static T instance;
		return &instance;
	    }
    };
    
}

#endif//SINGLETON_H
