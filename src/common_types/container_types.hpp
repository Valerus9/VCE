#pragma once

#include <vector>
#include "dcon.hpp"

//Due to forward declaration the following lines are needed (DO NOT REMOVE):
namespace sys {		//Due to forward declaration this line is needed. (DO NOT REMOVE)
	struct state;	//Due to forward declaration this line is needed. (DO NOT REMOVE)
}					//Due to forward declaration this line is needed. (DO NOT REMOVE)
//Due to forward declaration the previous lines are needed (DO NOT REMOVE).

template<typename value_type, typename tag_type, typename allocator = std::allocator<value_type>>
class tagged_vector {
	private:
	std::vector<value_type, allocator> storage;

	public:
	using public_value_type = value_type;
	using public_tag_type = tag_type;

	tagged_vector() { }
	tagged_vector(tagged_vector<value_type, tag_type, allocator> const& other) noexcept : storage(other.storage) { }
	tagged_vector(tagged_vector<value_type, tag_type, allocator>&& other) noexcept : storage(std::move(other.storage)) { }
	tagged_vector(size_t size) {
		storage.resize(size);
	}

	tagged_vector& operator=(tagged_vector<value_type, tag_type, allocator> const& other) noexcept {
		storage = other.storage;
		return *this;
	}
	tagged_vector& operator=(tagged_vector<value_type, tag_type, allocator>&& other) noexcept {
		storage = std::move(other.storage);
		return *this;
	}
	value_type const& operator[](tag_type t) const {
		assert(size_t(t.index()) < storage.size());
		return *(storage.data() + t.index());
	}
	value_type& operator[](tag_type t) {
		assert(size_t(t.index()) < storage.size());
		return *(storage.data() + t.index());
	}
	template<typename... T>
	tag_type emplace_back(T&&... ts) {
		storage.emplace_back(std::forward<T>(ts)...);
		return tag_type(typename tag_type::value_base_t(storage.size() - 1));
	}
	value_type& safe_get(tag_type t) {
		if(t.index() >= std::ssize(storage))
			storage.resize(t.index() + 1);
		return storage[t.index()];
	}
	auto data() const {
		return storage.data();
	}
	auto data() {
		return storage.data();
	}
	auto array() const {
		return storage.data();
	}
	auto array() {
		return storage.data();
	}
	auto begin() const {
		return storage.begin();
	}
	auto end() const {
		return storage.end();
	}
	auto begin() {
		return storage.begin();
	}
	auto end() {
		return storage.end();
	}
	auto size() const {
		return storage.size();
	}
	auto ssize() const {
		return std::ssize(storage);
	}
	void resize(size_t size) {
		storage.resize(size);
	}
	void reserve(size_t size) {
		storage.reserve(size);
	}
	void pop_back() {
		storage.pop_back();
	}
	tag_type push_back(value_type const& v) {
		storage.push_back(v);
		return tag_type(typename tag_type::value_base_t(storage.size() - 1));
	}
	tag_type push_back(value_type&& v) {
		storage.push_back(std::move(v));
		return tag_type(typename tag_type::value_base_t(storage.size() - 1));
	}
	value_type& back() {
		return storage.back();
	}
	value_type const& back() const {
		return storage.back();
	}
};
