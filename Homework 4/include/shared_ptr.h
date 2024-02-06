#ifndef SHARED_PTR
#define SHARED_PTR

template<typename T>
class SharedPtr {
public:
    SharedPtr() {
        p = nullptr;
        cnt = new size_t(0);
    }

    explicit SharedPtr(T* ptr) {
        p = ptr;
        cnt = new size_t(1);
    }

    ~SharedPtr() {
        if (*cnt == 1) { delete p; }
        p = nullptr;
        *cnt -= 1;
    }

    SharedPtr(const SharedPtr&rhs) {
        p = rhs.p;
        cnt = rhs.cnt;
        *cnt += 1;
    };

    SharedPtr& operator=(const SharedPtr&rhs) {
        if (this != &rhs) {
            if (*cnt == 1) { delete p; }
            *cnt -= 1;
            p = rhs.p;
            cnt = rhs.cnt;
            *cnt += 1;
        }
        return *this;
    };

    SharedPtr(SharedPtr&&rhs) noexcept {
        p = std::move(rhs.p);
        cnt = std::move(rhs.cnt);
        rhs.p = nullptr;
        rhs.cnt = nullptr;
    }

    SharedPtr& operator=(SharedPtr&&rhs) noexcept {
        if (this != &rhs) {
            p = std::move(rhs.p);
            cnt = std::move(rhs.cnt);
            rhs.p = nullptr;
            rhs.cnt = nullptr;
        }
        return *this;
    }

    [[nodiscard]] size_t use_count() const {
        if (cnt != nullptr) { return *cnt; }
        return 0;
    }

    T* get() const { return p; }
    T& operator*() const { return *p; }
    T* operator->() const { return p; }

    void reset() {
        delete p;
        p = nullptr;
        *cnt = 0;
    }

    void reset(T* ptr) {
        delete p;
        p = ptr;
        *cnt = 1;
    }

    explicit operator bool() const { return p != nullptr; }

private:
    T* p;
    size_t* cnt;
};

template<typename T>
T* make_shared(T x) { return new T(x); }

#endif //SHARED_PTR
