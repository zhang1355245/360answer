#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
		static const size_t init_ = 20;
        vector():data_(NULL), size_(0),cap_(init_)
        {
			reserve(cap_);
        }

        explicit vector( size_t n, const T& value = T())
        {
			size_ = n;
			cap_ = init_;
			if (size_ >= cap_) {
				cap_ += size_;
			}
            data_ = (T*)malloc(sizeof(T)*cap_);
			// data_ = new T[n];
			
            for (int i = 0; i < size_; ++i)
            {
                data_[i] = value;
            }
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            data_ = rhs.data_;
            size_ = rhs.size_;
			cap_ = rhs.cap_;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                free(data_);
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }

        // set & get
		T& operator[](size_t index) 
		{
			assert(index<size_);
			return data_[index];
		}

        // set
		void push_back(const T& element) 
		{
			if (size_ >= cap_)
			{
				this->reserve(cap_ += init_);
			}
			int i = size_;
			data_[i] = element;
			++size_;
		}

		void pop_back() 
		{
			assert(size_ > 0);
			if (size_)
				--size_;
			data_[size_]= data_[size_+1];
		}

		void reserve(size_t new2)
		{
			assert(new2 >= size_);
			if (!data_) {
				data_ = (T*)malloc(sizeof(T)*new2);
			}
			else {
				if (new2 > cap_)
					data_=(T*)realloc(data_, sizeof(T)*new2);
					cap_ = new2;
			}	
		}

		void resize(size_t news, const T &x) {
			if (news < size_)
			{
				for (size_t i = news;i!=size_;++i)
				{
					data_[i]= data_[size_];
				}
			}else {
				if(news>=cap_)
				{
					reserve(cap_+=news);
				}
				for (size_t j = size_; j != news; ++j)
				{
					data_[j]=x;
				}
			}
			size_ = news;
		}

		void resize(size_t news)
		{
			assert(news<size_);
			this->resize(news, T());
		}

		const T& begin()
		{
			return data_[0];
		}

		const T& end()
		{
			if (_size){
				return data_[size_ - 1];
			}
		}

		void clear(){
			size_=0; 
			cap_=0;
			~vector();
		}

		bool empty() 
		{
			if (size_==0)
			{
				return true;
			}else{
				return false;
			}
		}

    public:
        T*      data_;
        size_t  size_;
		size_t  cap_;   // capacity 分配的大小
		// T* iterator;
		// const T* const_iterator;
    };
}

#endif