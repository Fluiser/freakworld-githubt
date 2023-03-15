#include <iterator>
#include <iostream>
namespace Math {
    // Range работает с числами.
    // Значит, что range - часть математической библиотеки...

    template<class T>
    class Range {
        T r_begin, r_end, r_step;
    
        class range_iterator{
            T i_begin, i_end, i_step;
            
        public:

            using value_type = T;
            using difference_type = T;
            using pointer = T*;
            using reference = T&;

            explicit range_iterator(T _begin, T _end, T _step): i_begin(_begin),
                                                                i_end(_end),
                                                                i_step(_step) {}
            range_iterator operator++()
            {
                i_begin += i_step;
                return (*this);
            }

            range_iterator operator++(int)
            {
                range_iterator iter = (*this);
                ++(*this);
                return iter;
            }

            bool operator==(const range_iterator& another) const
            {
                return (this->i_begin == another.i_begin);
            }

            bool operator!=(const range_iterator& another) const
            {
                return (this->i_begin != another.i_begin);
            }

            T operator*() const 
            {
                return i_begin;
            }
        };

        friend range_iterator;
    public:

        Range(T _begin, T _end, T _step):   r_begin(_begin),
                                            r_end(_end),
                                            r_step(_step) {}
        range_iterator begin()
        {
            return range_iterator(r_begin, r_end, r_step);
        }

        range_iterator end()
        {
            return range_iterator(r_end, r_end, r_step);
        }
    };
}