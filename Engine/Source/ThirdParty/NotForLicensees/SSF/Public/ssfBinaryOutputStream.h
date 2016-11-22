#ifndef _ssfBinaryOutputStream_h_
#define _ssfBinaryOutputStream_h_

#include "ssfBaseDataType.h"

#include <fstream>

namespace ssf
	{
	class ssfString;

	class ssfBinaryOutputStream 
		{
		public:
			ssfBinaryOutputStream();
			~ssfBinaryOutputStream();

			/** open a file for streaming
				*/
			bool OpenFile( const ssfString &path );

			/** close the opened file
				*/
			void CloseFile( bool write_crc_checksum = true );

			/** write a specific number of bytes to the output stream
				@param src source data buffer
				@param num_bytes number of bytes to write to the stream
				@param throw_on_fail if the write fails, throw an exception
				@param returns true on success
				*/
			bool Write( const void *src , uint64 num_bytes , bool throw_on_fail = false );
		
			/** write words of data to the output stream
				the words are converted to little endian, regardless on the platform
				@param src source data buffer
				@param throw_on_fail if the write fails, throw an exception
				@param returns true on success
				*/
			bool Write1ByteWord( const void *src , bool throw_on_fail = false );
			bool Write2ByteWord( const void *src , bool throw_on_fail = false );
			bool Write4ByteWord( const void *src , bool throw_on_fail = false );
			bool Write8ByteWord( const void *src , bool throw_on_fail = false );

			/** write a native type to the output stream
				the words are converted to little endian, regardless on the platform
				@param value the value 
				*/
			void WriteInt8( int8 value );
			void WriteUInt8( uint8 value );
			void WriteInt16( int16 value );
			void WriteUInt16( uint16 value );
			void WriteInt32( int32 value );
			void WriteUInt32( uint32 value );
			void WriteInt64( int64 value );
			void WriteUInt64( uint64 value );
			void WriteFloat( float value );
			void WriteDouble( double value );
			void WriteString( string value );

			/** get the number of bytes written to the stream, the current position in the stream
				*/
			uint64 GetCurrentPosition() const;

		private:
			template<int word_size> bool WriteNByteWord( const void *src , bool throw_on_fail );
			void FlushCacheToFile();

			uint64 CurrPos; // the current position

			uint64 CacheStartPos; // the cache position, where the data cache starts
			uint64 CacheEndPos; // the cache position, where the data cache ends
			int8 *Data; // the cache data area
			
			std::ofstream *FileObject; // the handle of the open file
			
			ssfCRC32 crc;

		};
	
	template<int word_size> bool ssfBinaryOutputStream::WriteNByteWord(const void *src, bool throw_on_fail)
	{
		// copy to temp variable, convert endianness if needed
		if (convert_endianness)
		{
			const int8 *s = (const int8 *)src;
			int8 buf[word_size];

			for (unsigned int i = 0; i<word_size; ++i)
			{
				buf[i] = s[(word_size - 1) - i];
			}

			// write to output
			if (!this->Write(buf, word_size, throw_on_fail))
			{
				return false;
			}
		}
		else
		{
			// write directly to output
			if (!this->Write(src, word_size, throw_on_fail))
			{
				return false;
			}
		}
		
		// done
		return true;
	}

	inline bool ssfBinaryOutputStream::Write1ByteWord(const void *src, bool throw_on_fail /*= false */)
		{
		return this->Write(src, 1, throw_on_fail);
		}

	inline bool ssfBinaryOutputStream::Write2ByteWord(const void *src, bool throw_on_fail /*= false */)
		{
		return this->WriteNByteWord<2>(src, throw_on_fail);
		}

	inline bool ssfBinaryOutputStream::Write4ByteWord(const void *src, bool throw_on_fail /*= false */)
		{
		return this->WriteNByteWord<4>(src, throw_on_fail);
		}

	inline bool ssfBinaryOutputStream::Write8ByteWord(const void *src, bool throw_on_fail /*= false */)
		{
		return this->WriteNByteWord<8>(src, throw_on_fail);
		}

	inline void ssfBinaryOutputStream::WriteInt8(int8 value)
		{
		this->Write1ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteUInt8(uint8 value)
		{
		this->Write1ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteInt16(int16 value)
		{
		this->Write2ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteUInt16(uint16 value)
		{
		this->Write2ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteInt32(int32 value)
		{
		this->Write4ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteUInt32(uint32 value)
		{
		this->Write4ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteInt64(int64 value)
		{
		this->Write8ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteUInt64(uint64 value)
		{
		this->Write8ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteFloat(float value)
		{
		this->Write4ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteDouble(double value)
		{
		this->Write8ByteWord((void*)&value, true);
		}

	inline void ssfBinaryOutputStream::WriteString(string value)
		{
		uint32 size = (uint32)value.size();
		this->WriteUInt32(size);
		if (size > 0)
			{
			this->Write(value.c_str(), size, true);
			}
		}

	inline uint64 ssfBinaryOutputStream::GetCurrentPosition() const
		{
		return this->CurrPos;
		}

	};


#endif//_ssfBinaryOutputStream_h_ 