#include <type_traits>
#include <utility>
#include <tuple>

namespace rz
{
namespace details
{
template <class T> std::add_lvalue_reference_t<T> declval();

namespace adl
{
using std::begin;
using std::end;
template <class T> auto adlbegin(T &&t)
{
    return begin(std::forward<T>(t));
}
template <class T> auto adlend(T &&t)
{
    return end(std::forward<T>(t));
}
} // namespace adl
} // namespace details

/// Create an iterable enumerate wrapper around the iterable. The returned
/// iterator will return the index and the value.
///
/// \param t the iterable to iterate over.
/// \return an iterable enumerate wrapper.
/// \type T the iterable type to iterate over.
template <class T,
          class TI = decltype(details::adl::adlbegin(details::declval<T>()))
         >
constexpr auto enumerate(T &&t)
{
    struct iterator
    {
        size_t i;
        TI iter;

        bool operator != (const iterator &other) const
        {
            return iter != other.iter;
        }

        iterator& operator++ ()
        {
            ++this->i;
            ++this->iter;
            return *this;
        }

        auto operator* () const
        {
            return std::tie(this->i, *this->iter);
        }
    };

    struct wrapper
    {
        T iterable;

        auto begin()
        {
            return iterator{0, details::adl::adlbegin(iterable)};
        }

        auto end()
        {
            return iterator{0, details::adl::adlend(iterable)};
        }
    };

    return wrapper{ std::forward<T>(t) };
}
} // namespace rz
