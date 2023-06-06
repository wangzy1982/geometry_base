#ifndef _WGEO_CORE_SLICE_
#define _WGEO_CORE_SLICE_

#include <memory>

template<class T> 
class Slice;

template<class T>
class SliceData {
private:
    friend class Slice<T>;
    int m_ref_count;
    int m_capacity;
    T* m_data;
};

template<class T>
class Slice {
public:
    Slice(int capacity) {
        m_data = new SliceData<T>();
        m_data->m_ref_count = 0;
        m_data->m_capacity = capacity;
        if (capacity == 0) {
            m_data->m_data = nullptr;
        } else {
            m_data->m_data = new T[capacity];
        }
        m_start = 0;
        m_count = 0;
        Ref();
    }

    Slice() : Slice(0) {       
    }

    virtual ~Slice() {
        Unref();
    }

    void Append(const T& t) {
        if (m_data->m_ref_count == 1) {
            int i = m_start + m_count;
            if (m_data->m_capacity <= i) {
                T* old_data = m_data->m_data;
                m_data->m_capacity = m_data->m_capacity / 2 * 3 + 4;
                m_data->m_data = new T[m_data->m_capacity];
                memcpy(m_data->m_data, old_data, m_count * sizeof(T));
            }
            m_data->m_data[i] = t;
            m_count++;
        } else {
            Unref();
            SliceData<T>* old_data = m_data;
            m_data = new SliceData<T>();
            m_data->m_ref_count = 0;
            m_data->m_capacity = m_count;
            if (m_count == 0) {
                m_data->m_data = nullptr;
            } else {
                m_data->m_data = new T[m_count];
                memcpy(m_data->m_data, old_data->m_data + m_start, m_count * sizeof(T));
            }
            m_start = 0;
            Ref();
        }
    }

    T GetItem(int i) const {
        return m_data->m_data[m_start + i];
    }

    int Count() const {
        return m_count;
    }

    T* Clone() {
        if (m_count == 0) {
            return nullptr;
        }
        T* data = new T[m_count];
        memcpy(data, m_data->m_data + m_start, m_count * sizeof(T));
        return data;
    }

    Slice<T>& operator=(const Slice<T>& slice) {
        Unref();
        m_data = slice.m_data;
        m_start = slice.m_start;
        m_count = slice.m_count;
        Ref();
        return *this;
    }
private:
    void Ref() {
        ++m_data->m_ref_count;
    }

    void Unref() {
        if (--m_data->m_ref_count == 0) {
            if (m_data->m_data) {
                delete [] m_data->m_data;
            }
            delete m_data;
        }
    }
private:
    SliceData<T>* m_data;
    int m_start;
    int m_count;
};

#endif