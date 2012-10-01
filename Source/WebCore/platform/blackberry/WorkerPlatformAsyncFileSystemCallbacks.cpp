/*
 * Copyright (C) 2012 Research In Motion Limited. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 */

#include "config.h"
#if ENABLE(FILE_SYSTEM) && ENABLE(WORKERS)
#include "WorkerPlatformAsyncFileSystemCallbacks.h"

#include "CrossThreadTask.h"
#include "WorkerAsyncFileSystemBlackBerry.h"
#include "WorkerAsyncFileWriterBlackBerry.h"
#include "WorkerContext.h"
#include "WorkerLoaderProxy.h"
#include "WorkerThread.h"

#include <wtf/MainThread.h>

namespace WebCore {

static void performTaskOnMainThread(void* context)
{
    OwnPtr<ScriptExecutionContext::Task> task = adoptPtr(static_cast<ScriptExecutionContext::Task*>(context));
    task->performTask(0);
}

void postTaskToMainThread(PassOwnPtr<ScriptExecutionContext::Task> task)
{
    callOnMainThread(&performTaskOnMainThread, task.leakPtr());
}

template<> struct CrossThreadCopierBase<false, false, BlackBerry::Platform::WebFileInfo> {
    typedef BlackBerry::Platform::WebFileInfo Type;
    static Type copy(const Type& info)
    {
        Type result;
        result.m_modificationTime = info.m_modificationTime;
        result.m_length = info.m_length;
        result.m_type = info.m_type;
        result.m_platformPath.assign(info.m_platformPath);
        return result;
    }
};

template <> struct CrossThreadCopierBase<false, false, std::vector<BlackBerry::Platform::WebFileSystemEntry> > {
    typedef std::vector<BlackBerry::Platform::WebFileSystemEntry> Type;
    static Type copy(const Type& entries)
    {
        Type result(entries.size());
        for (size_t i = 0; i < entries.size(); ++i) {
            result[i].m_name.assign(entries[i].m_name);
            result[i].m_isDirectory = entries[i].m_isDirectory;
        }
        return result;
    }
};

void WorkerPlatformAsyncFileSystemCallbacks::notifyStop()
{
    m_callbacks.clear();
    {
        WTF::MutexLocker locker(m_mutex);
        m_context = 0;
    }
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyOpenFileSystem(BlackBerry::Platform::WebFileSystem* platformFileSystem)
{
    WTF::MutexLocker locker(m_mutex);
    if (!m_context) {
        PlatformAsyncFileSystemCallbacks::deleteMe();
        return;
    }

    postTaskToWorkerThread(createCallbackTask(&notifyOpenFileSystemOnWorkerThread, this, platformFileSystem));
}

void WorkerPlatformAsyncFileSystemCallbacks::notifySucceed()
{
    WTF::MutexLocker locker(m_mutex);
    if (!m_context) {
        PlatformAsyncFileSystemCallbacks::deleteMe();
        return;
    }

    postTaskToWorkerThread(createCallbackTask(&notifySucceedOnWorkerThread, this));
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyFail(BlackBerry::Platform::WebFileError error)
{
    WTF::MutexLocker locker(m_mutex);
    if (!m_context) {
        PlatformAsyncFileSystemCallbacks::deleteMe();
        return;
    }

    postTaskToWorkerThread(createCallbackTask(&notifyFailOnWorkerThread, this, error));
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyReadMetadata(const BlackBerry::Platform::WebFileInfo& fileInfo)
{
    WTF::MutexLocker locker(m_mutex);
    if (!m_context) {
        PlatformAsyncFileSystemCallbacks::deleteMe();
        return;
    }

    postTaskToWorkerThread(createCallbackTask(&notifyReadMetadataOnWorkerThread, this, fileInfo));
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyReadDirectory(const std::vector<BlackBerry::Platform::WebFileSystemEntry>& entries, bool hasMore)
{
    WTF::MutexLocker locker(m_mutex);
    if (!m_context) {
        PlatformAsyncFileSystemCallbacks::deleteMe();
        return;
    }

    postTaskToWorkerThread(createCallbackTask(&notifyReadDirectoryEntryOnWorkerThread, this, entries, hasMore));
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyCreateFileWriter(BlackBerry::Platform::WebFileWriter* platformWriter, long long length)
{
    WTF::MutexLocker locker(m_mutex);
    if (!m_context) {
        PlatformAsyncFileSystemCallbacks::deleteMe();
        return;
    }

    postTaskToWorkerThread(createCallbackTask(&notifyCreateFileWriterOnWorkerThread, this, platformWriter, length));
}

PassOwnPtr<AsyncFileSystem> WorkerPlatformAsyncFileSystemCallbacks::createAsyncFileSystem(PassOwnPtr<BlackBerry::Platform::WebFileSystem> platformFileSystem)
{
    return WorkerAsyncFileSystemBlackBerry::create(m_context, m_mode, platformFileSystem);
}

PassOwnPtr<AsyncFileWriter> WorkerPlatformAsyncFileSystemCallbacks::createAsyncFileWriter(PassOwnPtr<BlackBerry::Platform::WebFileWriter> platformWriter)
{
    ASSERT(m_writerClient);
    BlackBerry::Platform::WebFileWriter* platformWriterPtr = platformWriter.get();
    OwnPtr<WorkerAsyncFileWriterBlackBerry> writer = WorkerAsyncFileWriterBlackBerry::create(m_context, m_mode, platformWriter, m_writerClient);
    platformWriterPtr->setClient(writer->platformWriterClient());
    return writer.release();
}

void WorkerPlatformAsyncFileSystemCallbacks::deleteMe()
{
    deleteGuardedObject(this);
}

void WorkerPlatformAsyncFileSystemCallbacks::postTaskToWorkerThread(PassOwnPtr<ScriptExecutionContext::Task> task)
{
    m_context->thread()->workerLoaderProxy().postTaskForModeToWorkerContext(task, m_mode);
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyOpenFileSystemOnWorkerThread(ScriptExecutionContext*, WorkerPlatformAsyncFileSystemCallbacks* callbacks, BlackBerry::Platform::WebFileSystem* platformFileSystem)
{
    callbacks->PlatformAsyncFileSystemCallbacks::notifyOpenFileSystem(platformFileSystem);
}

void WorkerPlatformAsyncFileSystemCallbacks::notifySucceedOnWorkerThread(ScriptExecutionContext*, WorkerPlatformAsyncFileSystemCallbacks* callbacks)
{
    callbacks->PlatformAsyncFileSystemCallbacks::notifySucceed();
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyFailOnWorkerThread(ScriptExecutionContext*, WorkerPlatformAsyncFileSystemCallbacks* callbacks, BlackBerry::Platform::WebFileError error)
{
    callbacks->PlatformAsyncFileSystemCallbacks::notifyFail(error);
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyReadMetadataOnWorkerThread(ScriptExecutionContext*, WorkerPlatformAsyncFileSystemCallbacks* callbacks, const BlackBerry::Platform::WebFileInfo& fileInfo)
{
    callbacks->PlatformAsyncFileSystemCallbacks::notifyReadMetadata(fileInfo);
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyReadDirectoryEntryOnWorkerThread(ScriptExecutionContext*, WorkerPlatformAsyncFileSystemCallbacks* callbacks, const std::vector<BlackBerry::Platform::WebFileSystemEntry>& entries, bool hasMore)
{
    callbacks->PlatformAsyncFileSystemCallbacks::notifyReadDirectory(entries, hasMore);
}

void WorkerPlatformAsyncFileSystemCallbacks::notifyCreateFileWriterOnWorkerThread(ScriptExecutionContext*, WorkerPlatformAsyncFileSystemCallbacks* callbacks, BlackBerry::Platform::WebFileWriter* platformWriter, long long length)
{
    callbacks->PlatformAsyncFileSystemCallbacks::notifyCreateFileWriter(platformWriter, length);
}

} // namespace WebCore
#endif