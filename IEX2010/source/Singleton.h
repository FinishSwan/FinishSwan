#pragma once

template<class T>
class Singleton
{
protected : 
	static T* m_instance;

public : 
	static T& GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new T();
		}
		return *m_instance;
	}

	static void	Release()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

template<class T>
T*  Singleton<T>::m_instance = nullptr;