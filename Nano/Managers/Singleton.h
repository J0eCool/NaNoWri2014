#pragma once

template <typename T>
class Singleton {
private:
	static T _instance;

protected:
	Singleton() { }

public:
	static T* getInstance() {
		return &_instance;
	}
};

template <typename T>
T Singleton<T>::_instance;

