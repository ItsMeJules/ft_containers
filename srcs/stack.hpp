#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
	public:
		typedef	T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
	protected:
		container_type	container_;
	public:
		explicit stack(const container_type& ctnr = container_type()) : container_(ctnr) {}

		bool empty() const {
			return container_.empty();
		}

		size_type size() const {
			return container_.size();
		}
		
		value_type& top() {
			return container_.back();
		}

		const value_type& top() const {
			return container_.front();
		}
		
		void push(const value_type& val) {
			container_.push_back(val);
		}
		
		void pop() {
			container_.pop_back();
		}

		friend bool	operator==(const stack<T ,Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container_ == rhs.container_;
		}

		friend bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container_ != rhs.container_;
		}

		friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container_ < rhs.container_;
		}

		friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container_ <= rhs.container_;
		}
		
		friend bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container_ > rhs.container_;
		}

		friend bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.container_ >= rhs.container_;
		}
};

}

#endif
