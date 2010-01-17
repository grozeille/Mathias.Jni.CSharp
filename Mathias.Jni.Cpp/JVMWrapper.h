#pragma once
#include "jni.h"
#include <vcclr.h>
#include <stdlib.h>

using namespace System;

namespace MathiasJniCpp {

	/* permet de manipuler la JVM */
	public ref class JVMWrapper abstract
	{
	internal:
		static JNIEnv *env;
		static JavaVM *jvm;
		static JavaVMInitArgs *vm_args;
	public:
		/* Permet d'initialiser une JVM */
		static void InitJvm(cli::array<String^>^ options)
		{
			vm_args = new JavaVMInitArgs();
			JavaVMOption* jvmOptions = new JavaVMOption[options->Length];
			
			for(int i = 0; i < options->Length; i++)
			{
				jvmOptions[i] = JavaVMOption();

				pin_ptr<const wchar_t> wch = PtrToStringChars(options[i]);

				size_t convertedChars = 0;
				size_t  sizeInBytes = ((options[i]->Length + 1) * 2);
				errno_t err = 0;
				jvmOptions[i].optionString = (char *)malloc(sizeInBytes);

				wcstombs_s(&convertedChars, jvmOptions[i].optionString, sizeInBytes, wch, sizeInBytes);			
			}
			
			vm_args->version = JNI_VERSION_1_2;
			vm_args->options = jvmOptions;
			vm_args->nOptions = options->Length;
			vm_args->ignoreUnrecognized = JNI_TRUE;

			JavaVM * nativeJvm;
			JNIEnv * nativeEnv;
			jint vmError = JNI_CreateJavaVM(&nativeJvm, (void **)&nativeEnv, vm_args);

			delete [] jvmOptions;
			jvmOptions = NULL;

			JVMWrapper::jvm = nativeJvm;
			JVMWrapper::env = nativeEnv;

			if(vmError < 0)
			{
				String^ error_source;			
				switch(vmError)
				{
				case JNI_OK: error_source = "success"; break;
				case JNI_ERR: error_source = "unknown error"; break;
				case JNI_EDETACHED: error_source = "thread detached from the VM"; break;
				case JNI_EVERSION: error_source = "JNI version error"; break;
				case JNI_ENOMEM: error_source = "not enough memory"; break;
				case JNI_EEXIST: error_source = "VM already created"; break;
				case JNI_EINVAL: error_source = "invalid arguments"; break;
				}
				throw gcnew Exception("Failed to create JVM, error number: " + vmError+" with means : "+error_source);
			}
		}

		/* libère la JVM courante */
		static void ReleaseJvm()
		{
			jint vmError = JVMWrapper::jvm->DestroyJavaVM();
			if(vmError < 0)
				throw gcnew Exception("Failed to destroy JVM, error number: " + vmError);
		}
	};
}
