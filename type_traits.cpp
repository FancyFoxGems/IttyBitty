/* [remove_const] DEFINITION (AS FOUND IN BOOST'S TYPE TRAITS LIBRARY) */

template <class T>
struct remove_const
{
	typedef T type;
};

template <class T>
struct remove_const<const T>
{
	typedef T type;
};
