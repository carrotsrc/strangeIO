#include "framework/memory/CachePtr.hpp"

using namespace StrangeIO::Memory;

CachePtr::CachePtr(const PcmSample* block, unsigned int num_blocks, CacheUtilityInterface* cache) :
m_cache(cache), m_num_blocks(num_blocks)
{ 
	m_block = const_cast<PcmSample*>(block);
}

CachePtr::~CachePtr() {
	if(m_block == nullptr) return;

	m_cache->free_raw(m_block);
}

unsigned int CachePtr::block_size() const {
	return m_cache->block_size();
}

unsigned int CachePtr::num_blocks() const {
	return m_num_blocks;
}

const PcmSample* CachePtr::release() {
	auto ptr = m_block;
	m_block = nullptr;
	return ptr;
}

const PcmSample* CachePtr::get() const {
	return m_block;
}

void CachePtr::reset(const PcmSample* ptr) {
	if(m_block != nullptr) {
		m_cache->free_raw(m_block);
	}

	m_block = const_cast<PcmSample*>(ptr);
}

void CachePtr::swap(CachePtr& cptr) {
	auto ptr = cptr.release();
	cptr.reset(release());
	reset(ptr);
}

const PcmSample* CachePtr::operator *() const {
	return m_block;
}

PcmSample CachePtr::operator [](int index) const {
	return m_block[index];
}