#ifndef BASICS_RAW_PTR_H_INCLUDED
#define BASICS_RAW_PTR_H_INCLUDED

#include <memory>

namespace std {
    template <class T>
    class raw_ptr {
    private:
        T* _pointer;
    public:
        constexpr raw_ptr() = default;
        constexpr raw_ptr(const raw_ptr<T>& in) = default;
        constexpr raw_ptr<T>& operator= (const raw_ptr<T>& in) = default;
        constexpr raw_ptr(raw_ptr<T>&& in) = default;
        constexpr raw_ptr<T>& operator= (raw_ptr<T>&& in) = default;
        ~raw_ptr() = default;

        constexpr raw_ptr(unique_ptr<T>& in) noexcept {
            this->_pointer = in.get();
        }

        constexpr raw_ptr<T>& operator= (unique_ptr<T>& in) noexcept {
            this->_pointer = in.get();
            return *this;
        }

        constexpr raw_ptr(T* in) {
            this->_pointer = in;
        }

        constexpr T* get() const noexcept {
            return this->_pointer;
        }

        constexpr T& operator* () const noexcept {
            return *get();
        }

        constexpr T* operator-> () const noexcept {
            return get();
        }

        constexpr explicit operator bool() const noexcept {
            return this->get() != nullptr;
        }

        constexpr void swap(raw_ptr<T>& other) noexcept {
            std::swap(this->_pointer, other._pointer);
        }
    };

    template <class T>
    constexpr void swap(raw_ptr<T>& ptr1, raw_ptr<T>& ptr2) noexcept {
        ptr1.swap(ptr2);
    }

    template <class T, class U>
    constexpr bool operator== (raw_ptr<T> ptr1, raw_ptr<U> ptr2) noexcept {
        return ptr1.get() == ptr2.get();
    }

    template <class T, class U>
    constexpr bool operator!= (raw_ptr<T> ptr1, raw_ptr<U> ptr2) noexcept {
        return ptr1.get() != ptr2.get();
    }

    template <class T>
    constexpr bool operator== (raw_ptr<T> ptr1, nullptr_t ptr2) noexcept {
        return !bool(ptr1);
    }

    template <class T>
    constexpr bool operator!= (raw_ptr<T> ptr1, nullptr_t ptr2) noexcept {
        return bool(ptr1);
    }
}

#endif //BASICS_RAW_PTR_H_INCLUDED