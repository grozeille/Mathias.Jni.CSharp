#pragma once

#include "jni.h"
#include <vcclr.h>
#include <stdlib.h>
#include <string.h>

using namespace System;

namespace MathiasJniCpp {

	ref class StringConverter
	{
	public:
		char * native;
		jstring java;
		String^ cli;

		StringConverter(jstring value)
		{
			this->java = value;
			jboolean isCopy = true;
			const char* c = JVMWrapper::env->GetStringUTFChars(value, &isCopy);
			int size = strlen(c);
			native = (char *)malloc(sizeof(char)*size + 1);
			native[size] = NULL; // fin de chaine
			memcpy(native, c, size);
			cli = gcnew String(native);
		}


		StringConverter(String^ value)
		{
			this->cli = value;

			// créer un char* natif Unicode à partir de la chaine CLR
			pin_ptr<const wchar_t> wch = PtrToStringChars(value);

			size_t convertedChars = 0;
			size_t  sizeInBytes = ((value->Length + 1) * 2);
			errno_t err = 0;
			native = (char *)malloc(sizeInBytes);

			err = wcstombs_s(&convertedChars, native, sizeInBytes, wch, sizeInBytes);
			
			// à partir de la chaine native, créer la version Java
			java = JVMWrapper::env->NewStringUTF(native);
		}

		virtual ~StringConverter(void)
		{
			JVMWrapper::env->ReleaseStringUTFChars(java, native);
			delete(native);
		}

	};
}
