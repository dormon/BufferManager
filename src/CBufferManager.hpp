#ifndef _CBUFFERMANAGER_HPP_
#define _CBUFFERMANAGER_HPP_

#include<GL/glew.h>
#include<iostream>
#include<vector>
#include<set>

namespace NDormon{
	/**
	 * @brief Represents buffer object on GPU
	 */
	class CBuffer
	{
		public:
			GLuint ID;///< ID of buffer
			GLsizeiptr Size;///< size of buffer
		public:
			/**
			 * @brief Buffer constructor
			 *
			 * @param Size size of buffer in bytes
			 * @param Data optional data
			 * @param Target optional target
			 * @param Usage optional usage
			 */
			CBuffer(GLsizeiptr Size,const GLvoid*Data=NULL,
					GLenum Target=GL_ARRAY_BUFFER,GLenum Usage=GL_STATIC_DRAW);
			/**
			 * @brief Destructor of buffer
			 */
			~CBuffer();
			/**
			 * @brief Returns buffer ID
			 *
			 * @return ID
			 */
			GLuint GetID();
			/**
			 * @brief Binds buffer to specific target
			 *
			 * @param Target target
			 */
			void Bind(GLenum Target);
			/**
			 * @brief Unbinds buffer from specific target
			 *
			 * @param Target target
			 */
			void UnBind(GLenum Target);
			/**
			 * @brief Binds range of buffer to specific target
			 *
			 * @param Target target
			 * @param Index target index
			 * @param Offset offset
			 * @param Size size of buffer
			 */
			void BindRange(GLenum Target,GLuint Index,GLintptr Offset,
					GLsizeiptr Size);
      /**
       * @brief Unbind buffer from specific target
       *
       * @param Target target
       * @param Index index
       */
      void UnBindRange(GLenum Target,GLuint Index);
			/**
			 * @brief Binds buffer t ospecific target
			 *
			 * @param Target target
			 * @param Index index
			 */
			void BindBase(GLenum Target,GLuint Index);
      /**
       * @brief Unbind buffer from specific target
       *
       * @param Target target
       * @param Index index
       */
      void UnBindBase(GLenum Target,GLuint Index);
			/**
			 * @brief Uploads data to GPU
			 *
			 * @param Data pointer to data
			 */
			void Upload(const GLvoid*Data);
			/**
			 * @brief Uploads data to GPU on specific offset
			 *
			 * @param Data data
			 * @param Offset offset
			 * @param Size size of data to copy
			 */
			void Upload(const GLvoid*Data,GLintptr Offset,GLsizeiptr Size);
			/**
			 * @brief Clears buffer
			 *
			 * @param InternalFormat internal format of buffer
			 * @param Format format of data
			 * @param Type type of data
			 * @param Data optional data
			 */
			void Clear(GLenum InternalFormat,GLenum Format,GLenum Type,
					const GLvoid*Data=NULL);
			/**
			 * @brief Clears specific region of buffer
			 *
			 * @param InternalFormat internal format of data
			 * @param Offset offset 
			 * @param Size size of data
			 * @param Format format of data
			 * @param Type type of data
			 * @param Data optional data
			 */
			void Clear(GLenum InternalFormat,GLintptr Offset,GLsizeiptr Size,
					GLenum Format,GLenum Type,const GLvoid*Data=NULL);
			/**
			 * @brief Maps buffer from specific target
			 *
			 * @param Target target
			 * @param Access allowed access
			 *
			 * @return returns pointer to data
			 */
			void*Map(GLenum Target,GLenum Access);
			/**
			 * @brief Maps specific range of buffer from specific target
			 *
			 * @param Target target
			 * @param Offset offset
			 * @param Length size of data
			 * @param Access allowed acces
			 *
			 * @return returns pointer to data
			 */
			void*Map(GLenum Target,GLintptr Offset,GLsizeiptr Length,GLenum Access);
			/**
			 * @brief Flushes specific region of buffer
			 *
			 * @param Target target
			 * @param Offet offset of region
			 * @param Length size of region
			 */
			void FlushMapped(GLenum Target,GLintptr Offset,GLsizeiptr Length);
			/**
			 * @brief Unmaps mapped buffer
			 *
			 * @param Target target, where was buffer mapped
			 */
			void UnMap(GLenum Target);
			/**
			 * @brief Invalidates specific region of buffer
			 *
			 * @param Offset offset of region
			 * @param Length size of region
			 */
			void Invalidate(GLintptr Offset,GLsizeiptr Length);
			/**
			 * @brief Invalidates buffer
			 */
			void Invalidate();
			/**
			 * @brief Copies data from another buffer into this buffer
			 *
			 * @param Buffer another buffer
			 */
			void operator &=(CBuffer*Buffer);
			/**
			 * @brief Copies data from another buffer into this buffer
			 *
			 * @param Buffer another buffer
			 */
			void Copy(CBuffer*Buffer);
			/**
			 * @brief Copy data to CPU
			 *
			 * @param Data pointer to CPU data
			 */
			void Download(GLvoid*Data);
			/**
			 * @brief Copy specific region of data to CPU
			 *
			 * @param Data pointer to CPU data
			 * @param Offset offset of region
			 * @param Size size of region
			 */
			void Download(GLvoid*Data,GLintptr Offset,GLsizeiptr Size);
	};

	class CBufferManager{
		private:
			std::set<CBuffer*>Buffers;
		public:
			/**
			 * @brief Destructor
			 */
			~CBufferManager();
			/**
			 * @brief Create new buffer in manager
			 *
			 * @param Size size of buffer in bytes
			 * @param Data data of buffer
			 * @param Target target
			 * @param Usage type of usage
			 *
			 * @return buffer
			 */
			CBuffer*New(GLsizeiptr Size,const GLvoid*Data=NULL,
					GLenum Target=GL_ARRAY_BUFFER,GLenum Usage=GL_STATIC_DRAW);
			/**
			 * @brief removes Buffer from buffer manager
			 *
			 * @param Buffer buffer
			 */
			void Remove(CBuffer*Buffer);

	};
}


#endif//_CBUFFERMANAGER_HPP_
