#ifndef __COMMON_H__
#define __COMMON_H__

namespace Common
{
	template<typename T> class Singleton
	{
	public:
		static T* Get()
		{
			return m_cSingleton;
		}

		static void Set(T* val)
		{
			if (val == NULL)
				return;

			m_cSingleton = val;
		}

		static void Destroy()
		{
			delete m_cSingleton;
			m_cSingleton = NULL;
		}

	private:
		static T* m_cSingleton;
	};

	template <typename T> T* Singleton<T>::m_cSingleton = NULL;
}

#endif // !__COMMON_H__
