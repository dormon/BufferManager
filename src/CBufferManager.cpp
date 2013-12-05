#include"CBufferManager.hpp"
#include<iostream>

namespace NDormon{
	CBuffer::CBuffer(GLsizeiptr Size,const GLvoid*Data,
			GLenum Target,GLenum Usage){
		glGenBuffers(1,&this->ID);//generates name of buffer
		glBindBuffer(Target,this->ID);//bind buffer to target
		glBufferData(Target,Size,Data,Usage);//allocate data of buffer
		glBindBuffer(Target,0);//unbind buffer
	}

	CBuffer::~CBuffer(){
		glDeleteBuffers(1,&this->ID);//deletes buffer ID
	}

	void CBuffer::Bind(GLenum Target){
		glBindBuffer(Target,this->ID);//bind buffer to specific target
	}

	void CBuffer::UnBind(GLenum Target){
		glBindBuffer(Target,0);//unbind buffer from specific target
	}

	void CBuffer::BindRange(GLenum Target,GLuint Index,GLintptr Offset,
			GLsizeiptr Size){
		glBindBufferRange(Target,Index,this->ID,Offset,Size);//bind buffer range
	}

	void CBuffer::BindBase(GLenum Target,GLuint Index){
		glBindBufferBase(Target,Index,this->ID);//bind buffer base
	}

	void CBuffer::Upload(const GLvoid*Data){
		GLint Usage;//usage of buffer
		glGetBufferParameteriv(GL_VERTEX_ARRAY,GL_BUFFER_USAGE,&Usage);//get usage
		glBindBuffer(GL_VERTEX_ARRAY,this->ID);//bind buffer
		glBufferData(GL_VERTEX_ARRAY,this->Size,Data,Usage);//copy data
		glBindBuffer(GL_VERTEX_ARRAY,0);//unbind buffer
	}

	void CBuffer::Upload(
			const GLvoid*Data,
			GLintptr Offset,
			GLsizeiptr Size){
		glBindBuffer(GL_VERTEX_ARRAY,this->ID);//bind buffer
		glBufferSubData(GL_VERTEX_ARRAY,Offset,Size,Data);//copy data
		glBindBuffer(GL_VERTEX_ARRAY,0);//unbind buffer
	}

	void CBuffer::Clear(GLenum InternalFormat,GLenum Format,GLenum Type,
			const GLvoid*Data){
		glBindBuffer(GL_VERTEX_ARRAY,this->ID);//bind buffer
		glClearBufferSubData(GL_VERTEX_ARRAY,InternalFormat,0,//clear buffer
				this->Size,Format,Type,Data);
		glBindBuffer(GL_VERTEX_ARRAY,0);//unbind buffer
	}

	void CBuffer::Clear(GLenum InternalFormat,GLintptr Offset,GLsizeiptr Size,
			GLenum Format,GLenum Type,const GLvoid*Data){
		glBindBuffer(GL_VERTEX_ARRAY,this->ID);//bind buffer
		glClearBufferSubData(GL_VERTEX_ARRAY,InternalFormat,0,//clear buffer
				Size,Format,Type,Data);
		glBindBuffer(GL_VERTEX_ARRAY,0);//unbind buffer
	}

	void*CBuffer::Map(GLenum Target,GLenum Access){
		glBindBuffer(Target,this->ID);//bind buffer to target
		return glMapBuffer(Target,Access);//return mapped buffer
	}

	void*CBuffer::Map(
			GLenum Target,
			GLintptr Offset,
			GLsizeiptr Length,
			GLenum Access){
		glBindBuffer(Target,this->ID);//bind buffer to target
		return glMapBufferRange(Target,Offset,Length,Access);//return mapped region
	}

	void CBuffer::FlushMapped(GLenum Target,GLintptr Offset,GLsizeiptr Length){
		glFlushMappedBufferRange(Target,Offset,Length);//flush mapped buffer
	}

	void CBuffer::UnMap(GLenum Target){
		glUnmapBuffer(Target);//unmap buffer
		glBindBuffer(Target,0);//unbind buffer
	}

	void CBuffer::Invalidate(GLintptr Offset,GLsizeiptr Length){
		glInvalidateBufferSubData(this->ID,Offset,Length);//invalidate region
	}

	void CBuffer::Invalidate(){
		glInvalidateBufferData(this->ID);//invalidate buffer
	}

	void CBuffer::operator &=(CBuffer*Buffer){
		glBindBuffer(GL_COPY_READ_BUFFER,Buffer->ID);//bind read buffer
		glBindBuffer(GL_COPY_WRITE_BUFFER,this->ID);//bind write buffer
		GLsizeiptr MaxSize=(this->Size>Buffer->Size)?Buffer->Size:this->Size;//size
		glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,0,0,MaxSize);
		glBindBuffer(GL_COPY_READ_BUFFER,0);//unbind read buffer
		glBindBuffer(GL_COPY_WRITE_BUFFER,0);//unbind write buffer
	}

	void CBuffer::Copy(CBuffer*Buffer){
		glBindBuffer(GL_COPY_READ_BUFFER,Buffer->ID);//bind read buffer
		glBindBuffer(GL_COPY_WRITE_BUFFER,this->ID);//bind write buffer
		GLsizeiptr MaxSize=(this->Size>Buffer->Size)?Buffer->Size:this->Size;//size
		glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,0,0,MaxSize);
		glBindBuffer(GL_COPY_READ_BUFFER,0);//unbind read buffer
		glBindBuffer(GL_COPY_WRITE_BUFFER,0);//unbind write buffer
	}

	void CBuffer::Download(GLvoid*Data){
		glBindBuffer(GL_VERTEX_ARRAY,this->ID);//bind buffer
		glGetBufferSubData(GL_VERTEX_ARRAY,0,this->Size,Data);//obtain data
		glBindBuffer(GL_VERTEX_ARRAY,0);//unbin buffer
	}

	void CBuffer::Download(GLvoid*Data,GLintptr Offset,GLsizeiptr Size){
		glBindBuffer(GL_VERTEX_ARRAY,this->ID);//bind buffer
		glGetBufferSubData(GL_VERTEX_ARRAY,Offset,Size,Data);//obtain data
		glBindBuffer(GL_VERTEX_ARRAY,0);//unbin buffer
	}

}
