#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template<typename T>
class UniquePtr {
public:
    UniquePtr() { p = nullptr; }
    explicit UniquePtr(T* ptr) { p = ptr; }
    ~UniquePtr() { delete p; p = nullptr; }

    UniquePtr(const UniquePtr& rhs) = delete;
    UniquePtr& operator=(const UniquePtr& rhs) = delete;
    UniquePtr(UniquePtr&& rhs) noexcept {
        p = std::move(rhs.p);
        rhs.p = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& rhs) noexcept {
        if (this != &rhs) {
            delete p;
            p = std::move(rhs.p);
            rhs.p = nullptr;
        }
        return *this;
    }

    T* get() const { return p; }
    T& operator*() const { return *p; }
    T* operator->() const { return p; }
    void reset() { reset(nullptr); }
    void reset(T* ptr) { delete p; p = ptr; }
    T* release() {
        T* old = p;
        p = nullptr;
        return old;
    }

    explicit operator bool() const { return p != nullptr; }

private:
    T* p;
};

template<typename T>
T* make_unique(T x) { return new T(x); }

#endif //UNIQUE_PTR
