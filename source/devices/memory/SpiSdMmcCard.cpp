/**
 * \file
 * \brief SpiSdMmcCard class implementation
 *
 * \author Copyright (C) 2018 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/devices/memory/SpiSdMmcCard.hpp"

#include "distortos/devices/memory/SpiSdMmcCardProxy.hpp"

#include "estd/ScopeGuard.hpp"

namespace distortos
{

namespace devices
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

SpiSdMmcCard::~SpiSdMmcCard()
{

}

int SpiSdMmcCard::close()
{
	const Proxy proxy {*this};

	const auto ret = spiDevice_.close();

	if (proxy.isOpened() == false)
		proxy.deinitialize();

	return ret;
}

int SpiSdMmcCard::erase(const uint64_t address, const uint64_t size)
{
	return Proxy{*this}.erase(address, size);
}

size_t SpiSdMmcCard::getEraseBlockSize() const
{
	return blockSize;
}

std::pair<bool, uint8_t> SpiSdMmcCard::getErasedValue() const
{
	/// \todo implement by reading DATA_STAT_AFTER_ERASE from SCR register
	return {};
}

size_t SpiSdMmcCard::getProgramBlockSize() const
{
	return blockSize;
}

size_t SpiSdMmcCard::getReadBlockSize() const
{
	return blockSize;
}

uint64_t SpiSdMmcCard::getSize() const
{
	return blockSize * blocksCount_;
}

int SpiSdMmcCard::lock()
{
	return spiDevice_.lock();
}

int SpiSdMmcCard::open()
{
	const Proxy proxy {*this};

	const auto opened = proxy.isOpened();

	{
		const auto ret = spiDevice_.open();
		if (ret != 0)
			return ret;
	}

	if (opened == true)
		return {};

	auto closeScopeGuard = estd::makeScopeGuard(
			[this]()
			{
				close();
			});

	const auto ret = proxy.initialize();
	if (ret != 0)
		return ret;

	closeScopeGuard.release();
	return 0;
}

std::pair<int, size_t> SpiSdMmcCard::program(const uint64_t address, const void* const buffer, const size_t size)
{
	return Proxy{*this}.program(address, buffer, size);
}

std::pair<int, size_t> SpiSdMmcCard::read(const uint64_t address, void* const buffer, const size_t size)
{
	return Proxy{*this}.read(address, buffer, size);
}

int SpiSdMmcCard::synchronize()
{
	return {};
}

int SpiSdMmcCard::trim(uint64_t, uint64_t)
{
	return {};
}

int SpiSdMmcCard::unlock()
{
	return spiDevice_.unlock();
}

}	// namespace devices

}	// namespace distortos
