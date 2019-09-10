#pragma once

#include <cstdint>
#include <roapi.h>
#include <eventtoken.h>
#include <winstring.h>
#include <ole2.h>

MIDL_INTERFACE("DE87AD07-75DC-4EEC-9226-5628E98B9914")
IUnattendedUtilitiesStatics : public IInspectable
{
public:
	virtual HRESULT STDMETHODCALLTYPE RemoveUnattendedScript(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE RetrieveUnattendedScript(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE RetrieveAndRunUnattendedScriptAsync(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE RetrieveAndRunUnattendedScript(HRESULT* scriptResultHr, HSTRING* scriptOutput) = 0;
	virtual HRESULT STDMETHODCALLTYPE RunUnattendedScript(HSTRING scriptFileFullPath, HSTRING logFileFullPath, HRESULT* scriptResultHr, HSTRING* scriptOutput) = 0;
	virtual HRESULT STDMETHODCALLTYPE AbortUnattendedScript(void) = 0;
	virtual HRESULT STDMETHODCALLTYPE SendToastNotification(HSTRING title, HSTRING message) = 0;
	virtual HRESULT STDMETHODCALLTYPE IsScriptRunning(boolean* isRunning) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldRunOobeScript(boolean* shouldRun) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldRunOobeScript(boolean shouldRun) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldBlockUsbScripts(boolean* shouldBlock) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldBlockUsbScripts(boolean shouldBlock) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldSkipAbortToast(boolean* skip) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldSkipAbortToast(boolean skip) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldCallDevCenter(boolean* shouldCall) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldCallDevCenter(boolean shouldCall) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldBlockUnattendScripts(boolean* shouldBlock) = 0;
	virtual HRESULT STDMETHODCALLTYPE ShouldBlockUnattendScripts(boolean shouldBlock) = 0;
	virtual HRESULT STDMETHODCALLTYPE ScriptRunningChanged(int64_t* handler, EventRegistrationToken* token) = 0;
	virtual HRESULT STDMETHODCALLTYPE ScriptRunningChanged(EventRegistrationToken token) = 0;
	virtual HRESULT STDMETHODCALLTYPE HasUnattendedScriptOnUsb(boolean* hasScript) = 0;
	virtual HRESULT STDMETHODCALLTYPE RunUnattendedScriptOnUsbAsync(void) = 0;
};

const PCWSTR RuntimeClass_UnattendedUtilities = L"Microsoft.Xbox.Development.UnattendedUtilities";
const __declspec(selectany) IID& IID_IUnattendedUtilitiesStatics = _uuidof(IUnattendedUtilitiesStatics);