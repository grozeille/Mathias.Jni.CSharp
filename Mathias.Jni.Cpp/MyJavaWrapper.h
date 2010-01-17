#pragma once
#include "jni.h"
#include <stdlib.h>
#include "JVMWrapper.h"
#include "StringConverter.h"

using namespace System;

namespace MathiasJniCpp {

	/* représente ma class Java */
	public ref class MyJavaWrapper
	{
	private:
		static jmethodID initMethodId;
		static jmethodID getPeopleMethodId;
		static jmethodID setPeopleMethodId;
		static jmethodID sayHelloMethodId;

		static jclass clazz;
		jobject obj;

		/* initialise les metadata du coté Java */
		static void initJavaMetadata()
		{
			if(MyJavaWrapper::clazz == NULL)
			{
				MyJavaWrapper::clazz = JVMWrapper::env->FindClass("mathias/jni/java/MyJavaClass");
				MyJavaWrapper::initMethodId = JVMWrapper::env->GetMethodID(MyJavaWrapper::clazz, "<init>", "()V");
				MyJavaWrapper::getPeopleMethodId = JVMWrapper::env->GetMethodID(MyJavaWrapper::clazz, "getPeople", "()Ljava/lang/String;");
				MyJavaWrapper::setPeopleMethodId = JVMWrapper::env->GetMethodID(MyJavaWrapper::clazz, "setPeople", "(Ljava/lang/String;)V");
				MyJavaWrapper::sayHelloMethodId = JVMWrapper::env->GetMethodID(MyJavaWrapper::clazz, "sayHello", "()Ljava/lang/String;");
			}
		}
	public:
		/* une personne à saluer */
		property String ^People
		{
			virtual String ^ get()
			{
				jstring result = (jstring)JVMWrapper::env->CallObjectMethod(this->obj, MyJavaWrapper::getPeopleMethodId);
				StringConverter converter(result);
				return converter.cli;
			}
			virtual void set(String^ value)
			{
				StringConverter converter(value);
				jstring jvalue = converter.java;
				JVMWrapper::env->CallVoidMethod(this->obj, MyJavaWrapper::setPeopleMethodId, jvalue);
			}
		}

		String ^SayHello()
		{
			jstring result = (jstring)JVMWrapper::env->CallObjectMethod(this->obj, MyJavaWrapper::sayHelloMethodId);
			StringConverter converter(result);
			return converter.cli;
		}

		MyJavaWrapper(void)
		{
			// histoire de récupérer toutes les métadatas nécessaires du coté Java
			MyJavaWrapper::initJavaMetadata();

			// construction d'une instance avec le constructeur par défaut
			this->obj = JVMWrapper::env->NewObject(MyJavaWrapper::clazz, MyJavaWrapper::initMethodId);			
		}
	public:

		virtual ~MyJavaWrapper(void)
		{
			JVMWrapper::env->DeleteLocalRef(this->obj);
		}
	};
}
