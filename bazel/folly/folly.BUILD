licenses(["notice"])

# Modified from https://github.com/bazelment/trunk/blob/master/third_party/folly/linux-k8/folly/

genrule(
    name = "generate_format_tables",
    srcs = [
        "folly/build/generate_format_tables.py"
    ],
    outs = [
        "folly/FormatTables.cpp",
    ],
    cmd = "$(location folly/build/generate_format_tables.py) --install_dir $(@D)"
)

genrule(
    name = "generate_escape_tables",
    srcs = [
        "folly/build/generate_escape_tables.py"
    ],
    outs = [
        "EscapeTables.cpp",
    ],
    cmd = "$(location folly/build/generate_escape_tables.py) --install_dir $(@D)"
)

genrule(
    name = "generate_varint_tables",
    srcs = [
        "folly/build/generate_varint_tables.py"
    ],
    outs = [
        "GroupVarintTables.cpp",
    ],
    cmd = "$(location folly/build/generate_varint_tables.py) --install_dir $(@D)"
)

folly_copts = [
    "-pthread",
    "-std=gnu++1y",
    "-Wno-unused-variable",
]

cc_library(
    name = "base",
    hdrs = [
        "folly/ApplyTuple.h",
        "folly/Arena-inl.h",
        "folly/Arena.h",
        "folly/Array.h",
        "folly/Assume.h",
        "folly/AtomicBitSet.h",
        "folly/AtomicHashArray-inl.h",
        "folly/AtomicHashArray.h",
        "folly/AtomicHashMap-inl.h",
        "folly/AtomicHashMap.h",
        "folly/AtomicIntrusiveLinkedList.h",
        "folly/AtomicLinkedList.h",
        "folly/AtomicStruct.h",
        "folly/AtomicUnorderedMap.h",
        "folly/Baton.h",
        "folly/Benchmark.h",
        "folly/Bits.h",
        "folly/CPortability.h",
        "folly/CachelinePadded.h",
        "folly/CallOnce.h",
        "folly/Checksum.h",
        "folly/Chrono.h",
        "folly/ClockGettimeWrappers.h",
        "folly/ConcurrentSkipList-inl.h",
        "folly/ConcurrentSkipList.h",
        "folly/ConstexprMath.h",
        "folly/ContainerTraits.h",
        "folly/Conv.h",
        "folly/CppAttributes.h",
        "folly/CpuId.h",
        "folly/Demangle.h",
        "folly/DiscriminatedPtr.h",
        "folly/DynamicConverter.h",
        "folly/Enumerate.h",
        "folly/EvictingCacheMap.h",
        "folly/Exception.h",
        "folly/ExceptionString.h",
        "folly/ExceptionWrapper-inl.h",
        "folly/ExceptionWrapper.h",
        "folly/Executor.h",
        "folly/Expected.h",
        "folly/FBString.h",
        "folly/FBVector.h",
        "folly/File.h",
        "folly/FileUtil.h",
        "folly/Fingerprint.h",
        "folly/FixedString.h",
        "folly/Foreach.h",
        "folly/Foreach-inl.h",
        "folly/Format-inl.h",
        "folly/Format.h",
        "folly/FormatArg.h",
        "folly/FormatTraits.h",
        "folly/Function.h",
        "folly/Functional.h",
        "folly/GlobalThreadPoolList.h",
        "folly/GroupVarint.h",
        "folly/Hash.h",
        "folly/IPAddress.h",
        "folly/IPAddressException.h",
        "folly/IPAddressV4.h",
        "folly/IPAddressV6.h",
        "folly/Indestructible.h",
        "folly/IndexedMemPool.h",
        "folly/IntrusiveList.h",
        "folly/Iterator.h",
        "folly/Launder.h",
        "folly/Lazy.h",
        "folly/LifoSem.h",
        "folly/Likely.h",
        "folly/LockTraits.h",
        "folly/LockTraitsBoost.h",
        "folly/Logging.h",
        "folly/MPMCPipeline.h",
        "folly/MPMCQueue.h",
        "folly/MacAddress.h",
        "folly/MallctlHelper.h",
        "folly/Malloc.h",
        "folly/MapUtil.h",
        "folly/Math.h",
        "folly/Memory.h",
        "folly/MemoryMapping.h",
        "folly/MicroLock.h",
        "folly/MicroSpinLock.h",
        "folly/MoveWrapper.h",
        "folly/Optional.h",
        "folly/Overload.h",
        "folly/PackedSyncPtr.h",
        "folly/Padded.h",
        "folly/Partial.h",
        "folly/PicoSpinLock.h",
        "folly/Portability.h",
        "folly/Preprocessor.h",
        "folly/PriorityMPMCQueue.h",
        "folly/ProducerConsumerQueue.h",
        "folly/RWSpinLock.h",
        "folly/Random-inl.h",
        "folly/Random.h",
        "folly/Range.h",
        "folly/Replaceable.h",
        "folly/SafeAssert.h",
        "folly/ScopeGuard.h",
        "folly/SharedMutex.h",
        "folly/Shell.h",
        "folly/Singleton-inl.h",
        "folly/Singleton.h",
        "folly/SingletonThreadLocal.h",
        "folly/SmallLocks.h",
        "folly/SocketAddress.h",
        "folly/SparseByteSet.h",
        "folly/SpinLock.h",
        "folly/String-inl.h",
        "folly/String.h",
        "folly/Subprocess.h",
        "folly/Synchronized.h",
        "folly/SynchronizedPtr.h",
        "folly/ThreadCachedArena.h",
        "folly/ThreadCachedInt.h",
        "folly/ThreadId.h",
        "folly/ThreadLocal.h",
        "folly/ThreadName.h",
        "folly/TimeoutQueue.h",
        "folly/TokenBucket.h",
        "folly/Traits.h",
        "folly/Try-inl.h",
        "folly/Try.h",
        "folly/UncaughtExceptions.h",
        "folly/Unicode.h",
        "folly/Unit.h",
        "folly/Uri-inl.h",
        "folly/Uri.h",
        "folly/Utility.h",
        "folly/Varint.h",
        "folly/VersionCheck.h",
        "folly/concurrency/AtomicSharedPtr.h",
        "folly/concurrency/CacheLocality.h",
        "folly/concurrency/ConcurrentHashMap.h",
        "folly/concurrency/CoreCachedSharedPtr.h",
        "folly/concurrency/detail/AtomicSharedPtr-detail.h",
        "folly/concurrency/detail/ConcurrentHashMap-detail.h",
        "folly/detail/AtomicHashUtils.h",
        "folly/detail/AtomicUnorderedMapUtils.h",
        "folly/detail/AtomicUtils.h",
        "folly/detail/BitIteratorDetail.h",
        "folly/detail/ChecksumDetail.h",
        "folly/detail/DiscriminatedPtrDetail.h",
        "folly/detail/FileUtilDetail.h",
        "folly/detail/FingerprintPolynomial.h",
        "folly/detail/Futex.h",
        "folly/detail/GroupVarintDetail.h",
        "folly/detail/IPAddress.h",
        "folly/detail/IPAddressSource.h",
        "folly/detail/MPMCPipelineDetail.h",
        "folly/detail/MallocImpl.h",
        "folly/detail/MemoryIdler.h",
        "folly/detail/RangeCommon.h",
        "folly/detail/RangeSse42.h",
        "folly/detail/Sleeper.h",
        "folly/detail/SlowFingerprint.h",
        "folly/detail/SocketFastOpen.h",
        "folly/detail/StaticSingletonManager.h",
        "folly/detail/ThreadLocalDetail.h",
        "folly/detail/TurnSequencer.h",
        "folly/detail/UncaughtExceptionCounter.h",
        "folly/dynamic-inl.h",
        "folly/dynamic.h",
        "folly/executors/Async.h",
        "folly/executors/BlockingQueue.h",
        "folly/executors/Codel.h",
        "folly/executors/CPUThreadPoolExecutor.h",
        "folly/executors/FiberIOExecutor.h",
        "folly/executors/FutureExecutor.h",
        "folly/executors/GlobalExecutor.h",
        "folly/executors/IOExecutor.h",
        "folly/executors/IOObjectCache.h",
        "folly/executors/IOThreadPoolExecutor.h",
        "folly/executors/LifoSemMPMCQueue.h",
        "folly/executors/NamedThreadFactory.h",
        "folly/executors/PriorityLifoSemMPMCQueue.h",
        "folly/executors/PriorityThreadFactory.h",
        "folly/executors/SerialExecutor.h",
        "folly/executors/ThreadedExecutor.h",
        "folly/executors/ThreadFactory.h",
        "folly/executors/ThreadPoolExecutor.h",
        "folly/executors/UnboundedBlockingQueue.h",
        "folly/experimental/AsymmetricMemoryBarrier.h",
        "folly/experimental/AutoTimer.h",
        "folly/experimental/BitVectorCoding.h",
        "folly/experimental/Bits.h",
        "folly/experimental/CodingDetail.h",
        "folly/experimental/DynamicParser-inl.h",
        "folly/experimental/DynamicParser.h",
        "folly/experimental/EliasFanoCoding.h",
        "folly/experimental/EnvUtil.h",
        "folly/experimental/EventCount.h",
        "folly/experimental/ExecutionObserver.h",
        "folly/experimental/FunctionScheduler.h",
        "folly/experimental/FutureDAG.h",
        "folly/experimental/Instructions.h",
        "folly/experimental/JSONSchema.h",
        "folly/experimental/JemallocNodumpAllocator.h",
        "folly/experimental/LockFreeRingBuffer.h",
        "folly/experimental/NestedCommandLineApp.h",
        "folly/experimental/ProgramOptions.h",
        "folly/experimental/ReadMostlySharedPtr.h",
        "folly/experimental/Select64.h",
        "folly/experimental/StampedPtr.h",
        "folly/experimental/StringKeyedCommon.h",
        "folly/experimental/StringKeyedMap.h",
        "folly/experimental/StringKeyedSet.h",
        "folly/experimental/StringKeyedUnorderedMap.h",
        "folly/experimental/StringKeyedUnorderedSet.h",
        "folly/experimental/TLRefCount.h",
        "folly/experimental/ThreadedRepeatingFunctionRunner.h",
        "folly/experimental/TupleOps.h",
        "folly/experimental/bser/Bser.h",
        "folly/experimental/exception_tracer/ExceptionAbi.h",
        "folly/experimental/exception_tracer/ExceptionCounterLib.h",
        "folly/experimental/exception_tracer/ExceptionTracer.h",
        "folly/experimental/exception_tracer/ExceptionTracerLib.h",
        "folly/experimental/exception_tracer/StackTrace.h",
        "folly/experimental/hazptr/debug.h",
        "folly/experimental/hazptr/hazptr.h",
        "folly/experimental/hazptr/hazptr-impl.h",
        "folly/experimental/hazptr/memory_resource.h",
        "folly/experimental/io/FsUtil.h",
        "folly/experimental/io/HugePages.h",
        "folly/experimental/logging/AsyncFileWriter.h",
        "folly/experimental/logging/GlogStyleFormatter.h",
        "folly/experimental/logging/ImmediateFileWriter.h",
        "folly/experimental/logging/Init.h",
        "folly/experimental/logging/LogCategory.h",
        "folly/experimental/logging/LogFormatter.h",
        "folly/experimental/logging/LogHandler.h",
        "folly/experimental/logging/LogLevel.h",
        "folly/experimental/logging/LogMessage.h",
        "folly/experimental/logging/LogName.h",
        "folly/experimental/logging/LogStream.h",
        "folly/experimental/logging/LogStreamProcessor.h",
        "folly/experimental/logging/LogWriter.h",
        "folly/experimental/logging/Logger.h",
        "folly/experimental/logging/LoggerDB.h",
        "folly/experimental/logging/RateLimiter.h",
        "folly/experimental/logging/StandardLogHandler.h",
        "folly/experimental/logging/printf.h",
        "folly/experimental/logging/xlog.h",
        "folly/experimental/observer/Observable-inl.h",
        "folly/experimental/observer/Observable.h",
        "folly/experimental/observer/Observer-inl.h",
        "folly/experimental/observer/Observer.h",
        "folly/experimental/observer/SimpleObservable-inl.h",
        "folly/experimental/observer/SimpleObservable.h",
        "folly/experimental/observer/detail/Core.h",
        "folly/experimental/observer/detail/GraphCycleDetector.h",
        "folly/experimental/observer/detail/Observer-pre.h",
        "folly/experimental/observer/detail/ObserverManager.h",
        "folly/experimental/symbolizer/Dwarf.h",
        "folly/experimental/symbolizer/Elf-inl.h",
        "folly/experimental/symbolizer/Elf.h",
        "folly/experimental/symbolizer/ElfCache.h",
        "folly/experimental/symbolizer/LineReader.h",
        "folly/experimental/symbolizer/SignalHandler.h",
        "folly/experimental/symbolizer/StackTrace.h",
        "folly/experimental/symbolizer/Symbolizer.h",
        "folly/fibers/AddTasks-inl.h",
        "folly/fibers/AddTasks.h",
        "folly/fibers/AtomicBatchDispatcher-inl.h",
        "folly/fibers/AtomicBatchDispatcher.h",
        "folly/fibers/BatchDispatcher.h",
        "folly/fibers/Baton-inl.h",
        "folly/fibers/Baton.h",
        "folly/fibers/BoostContextCompatibility.h",
        "folly/fibers/EventBaseLoopController-inl.h",
        "folly/fibers/EventBaseLoopController.h",
        "folly/fibers/Fiber-inl.h",
        "folly/fibers/Fiber.h",
        "folly/fibers/FiberManager-inl.h",
        "folly/fibers/FiberManager.h",
        "folly/fibers/FiberManagerInternal-inl.h",
        "folly/fibers/FiberManagerInternal.h",
        "folly/fibers/FiberManagerMap.h",
        "folly/fibers/ForEach-inl.h",
        "folly/fibers/ForEach.h",
        "folly/fibers/GenericBaton.h",
        "folly/fibers/GuardPageAllocator.h",
        "folly/fibers/LoopController.h",
        "folly/fibers/Promise-inl.h",
        "folly/fibers/Promise.h",
        "folly/fibers/Semaphore.h",
        "folly/fibers/SimpleLoopController.h",
        "folly/fibers/TimedMutex-inl.h",
        "folly/fibers/TimedMutex.h",
        "folly/fibers/TimeoutController.h",
        "folly/fibers/WhenN-inl.h",
        "folly/fibers/WhenN.h",
        "folly/fibers/detail/AtomicBatchDispatcher.h",
        "folly/fibers/traits.h",
        "folly/futures/Barrier.h",
        "folly/futures/DrivableExecutor.h",
        "folly/futures/Future-inl.h",
        "folly/futures/Future-pre.h",
        "folly/futures/Future.h",
        "folly/futures/FutureException.h",
        "folly/futures/FutureSplitter.h",
        "folly/futures/InlineExecutor.h",
        "folly/futures/ManualExecutor.h",
        "folly/futures/Promise-inl.h",
        "folly/futures/Promise.h",
        "folly/futures/QueuedImmediateExecutor.h",
        "folly/futures/ScheduledExecutor.h",
        "folly/futures/SharedPromise-inl.h",
        "folly/futures/SharedPromise.h",
        "folly/futures/ThreadWheelTimekeeper.h",
        "folly/futures/Timekeeper.h",
        "folly/futures/detail/Core.h",
        "folly/futures/detail/FSM.h",
        "folly/futures/detail/Types.h",
        "folly/futures/helpers.h",
        "folly/gen/Base-inl.h",
        "folly/gen/Base.h",
        "folly/gen/Combine-inl.h",
        "folly/gen/Combine.h",
        "folly/gen/Core-inl.h",
        "folly/gen/Core.h",
        "folly/gen/File-inl.h",
        "folly/gen/File.h",
        "folly/gen/Parallel-inl.h",
        "folly/gen/Parallel.h",
        "folly/gen/ParallelMap-inl.h",
        "folly/gen/ParallelMap.h",
        "folly/gen/String-inl.h",
        "folly/gen/String.h",
        "folly/hash/SpookyHashV1.h",
        "folly/hash/SpookyHashV2.h",
        "folly/init/Init.h",
        "folly/io/Compression.h",
        "folly/io/Cursor.h",
        "folly/io/Cursor-inl.h",
        "folly/io/IOBuf.h",
        "folly/io/IOBufQueue.h",
        "folly/io/RecordIO.h",
        "folly/io/RecordIO-inl.h",
        "folly/io/TypedIOBuf.h",
        "folly/io/ShutdownSocketSet.h",
        "folly/io/async/AsyncPipe.h",
        "folly/io/async/AsyncTimeout.h",
        "folly/io/async/AsyncTransport.h",
        "folly/io/async/AsyncUDPServerSocket.h",
        "folly/io/async/AsyncUDPSocket.h",
        "folly/io/async/AsyncServerSocket.h",
        "folly/io/async/AsyncSignalHandler.h",
        "folly/io/async/AsyncSocket.h",
        "folly/io/async/AsyncSocketBase.h",
        "folly/io/async/AsyncSSLSocket.h",
        "folly/io/async/AsyncSocketException.h",
        "folly/io/async/DecoratedAsyncTransportWrapper.h",
        "folly/io/async/DelayedDestructionBase.h",
        "folly/io/async/DelayedDestruction.h",
        "folly/io/async/DestructorCheck.h",
        "folly/io/async/EventBase.h",
        "folly/io/async/EventBaseLocal.h",
        "folly/io/async/EventBaseManager.h",
        "folly/io/async/EventBaseThread.h",
        "folly/io/async/EventFDWrapper.h",
        "folly/io/async/EventHandler.h",
        "folly/io/async/EventUtil.h",
        "folly/io/async/NotificationQueue.h",
        "folly/io/async/HHWheelTimer.h",
        "folly/io/async/SSLOptions.h",
        "folly/io/async/ssl/OpenSSLUtils.h",
        "folly/io/async/ssl/SSLErrors.h",
        "folly/io/async/ssl/TLSDefinitions.h",
        "folly/io/async/Request.h",
        "folly/io/async/SSLContext.h",
        "folly/io/async/ScopedEventBaseThread.h",
        "folly/io/async/TimeoutManager.h",
        "folly/io/async/VirtualEventBase.h",
        "folly/io/async/WriteChainAsyncTransportWrapper.h",
        "folly/io/compression/Utils.h",
        "folly/io/compression/Zlib.h",
        "folly/json.h",
        "folly/memory/UninitializedMemoryHacks.h",
        "folly/portability/Asm.h",
        "folly/portability/Atomic.h",
        "folly/portability/BitsFunctexcept.h",
        "folly/portability/Builtins.h",
        "folly/portability/Config.h",
        "folly/portability/Constexpr.h",
        "folly/portability/Dirent.h",
        "folly/portability/Event.h",
        "folly/portability/Fcntl.h",
        "folly/portability/GFlags.h",
        "folly/portability/GMock.h",
        "folly/portability/GTest.h",
        "folly/portability/IOVec.h",
        "folly/portability/Libgen.h",
        "folly/portability/Malloc.h",
        "folly/portability/Math.h",
        "folly/portability/Memory.h",
        "folly/portability/OpenSSL.h",
        "folly/portability/PThread.h",
        "folly/portability/Semaphore.h",
        "folly/portability/Sockets.h",
        "folly/portability/Stdio.h",
        "folly/portability/Stdlib.h",
        "folly/portability/String.h",
        "folly/portability/SysFile.h",
        "folly/portability/SysMembarrier.h",
        "folly/portability/SysMman.h",
        "folly/portability/SysResource.h",
        "folly/portability/SysStat.h",
        "folly/portability/SysSyscall.h",
        "folly/portability/SysTime.h",
        "folly/portability/SysTypes.h",
        "folly/portability/SysUio.h",
        "folly/portability/Syslog.h",
        "folly/portability/Time.h",
        "folly/portability/TypeTraits.h",
        "folly/portability/Unistd.h",
        "folly/portability/Windows.h",
        "folly/small_vector.h",
        "folly/sorted_vector_types.h",
        "folly/ssl/Init.h",
        "folly/ssl/OpenSSLCertUtils.h",
        "folly/ssl/OpenSSLHash.h",
        "folly/ssl/OpenSSLLockTypes.h",
        "folly/ssl/OpenSSLPtrTypes.h",
        "folly/ssl/OpenSSLVersionFinder.h",
        "folly/ssl/SSLSession.h",
        "folly/ssl/detail/OpenSSLThreading.h",
        "folly/ssl/detail/SSLSessionImpl.h",
        "folly/stats/BucketedTimeSeries-defs.h",
        "folly/stats/BucketedTimeSeries.h",
        "folly/stats/Histogram-defs.h",
        "folly/stats/Histogram.h",
        "folly/stats/MultiLevelTimeSeries-defs.h",
        "folly/stats/MultiLevelTimeSeries.h",
        "folly/stats/TimeseriesHistogram-defs.h",
        "folly/stats/TimeseriesHistogram.h",
        "folly/stats/detail/Bucket.h",
        "folly/stop_watch.h",
        "folly/tracing/ScopedTraceSection.h",
        "folly/tracing/StaticTracepoint-ELFx86.h",
        "folly/tracing/StaticTracepoint.h",
    ],
    srcs = [
        ":generate_escape_tables",
        ":generate_format_tables",
        "folly/Conv.cpp",
        "folly/Demangle.cpp",
        "folly/Format.cpp",
        "folly/FormatArg.cpp",
        "folly/MallctlHelper.cpp",
        "folly/String.cpp",
        "folly/Unicode.cpp",
        "folly/detail/RangeCommon.cpp",
        "folly/portability/BitsFunctexcept.cpp",
    ],
    includes = [
        ".",
    ],
    copts = folly_copts,
    deps = [
        "@boost//:system",
        "@boost//:locale",
        "@boost//:crc",
        "@boost//:implicit_cast",
        "@double_conversion//:double-conversion",
        "@//bazel/folly:folly_config",
        "@com_github_google_glog//:glog",
        "@jemalloc//:jemalloc",
        "@openssl//:ssl",
    ],
)

cc_binary(
    name = "generate_fingerprint_tables_bin",
    srcs = [
        "folly/build/GenerateFingerprintTables.cpp",
    ],
    deps = [
        ":base",
        "@com_github_gflags_gflags//:gflags",
    ],
)

genrule(
    name = "generate_fingerprint_tables",
    outs = [
        "FingerprintTables.cpp",
    ],
    tools = [
        ":generate_fingerprint_tables_bin"
    ],
    cmd = "$(location :generate_fingerprint_tables_bin) --install_dir $(@D)",
)

cc_library(
    name = "folly",
    srcs = [
        ":generate_fingerprint_tables",
        ":generate_varint_tables",
        "folly/Assume.cpp",
        "folly/Checksum.cpp",
        "folly/ClockGettimeWrappers.cpp",
        "folly/ExceptionWrapper.cpp",
        "folly/Executor.cpp",
        "folly/File.cpp",
        "folly/FileUtil.cpp",
        "folly/GlobalThreadPoolList.cpp",
        "folly/GroupVarint.cpp",
        "folly/IPAddress.cpp",
        "folly/IPAddressV4.cpp",
        "folly/IPAddressV6.cpp",
        "folly/LifoSem.cpp",
        "folly/MacAddress.cpp",
        "folly/MemoryMapping.cpp",
        "folly/MicroLock.cpp",
        "folly/Optional.cpp",
        "folly/Random.cpp",
        "folly/SafeAssert.cpp",
        "folly/ScopeGuard.cpp",
        "folly/SharedMutex.cpp",
        "folly/Shell.cpp",
        "folly/Singleton.cpp",
        "folly/SocketAddress.cpp",
        "folly/Subprocess.cpp",
        "folly/ThreadCachedArena.cpp",
        "folly/ThreadName.cpp",
        "folly/TimeoutQueue.cpp",
        "folly/Try.cpp",
        "folly/Uri.cpp",
        "folly/Version.cpp",
        "folly/concurrency/CacheLocality.cpp",
        "folly/detail/Futex.cpp",
        "folly/detail/IPAddress.cpp",
        "folly/detail/MemoryIdler.cpp",
        "folly/detail/SocketFastOpen.cpp",
        "folly/detail/StaticSingletonManager.cpp",
        "folly/detail/ThreadLocalDetail.cpp",
        "folly/dynamic.cpp",
        "folly/executors/CPUThreadPoolExecutor.cpp",
        "folly/executors/Codel.cpp",
        "folly/executors/GlobalExecutor.cpp",
        "folly/executors/IOThreadPoolExecutor.cpp",
        "folly/executors/SerialExecutor.cpp",
        "folly/executors/ThreadPoolExecutor.cpp",
        "folly/executors/ThreadedExecutor.cpp",
        "folly/experimental/AsymmetricMemoryBarrier.cpp",
        "folly/experimental/DynamicParser.cpp",
        "folly/experimental/EnvUtil.cpp",
        "folly/experimental/FunctionScheduler.cpp",
        "folly/experimental/JSONSchema.cpp",
        "folly/experimental/JemallocNodumpAllocator.cpp",
        "folly/experimental/NestedCommandLineApp.cpp",
        "folly/experimental/ProgramOptions.cpp",
        "folly/experimental/Select64.cpp",
        "folly/experimental/ThreadedRepeatingFunctionRunner.cpp",
        "folly/experimental/bser/Dump.cpp",
        "folly/experimental/bser/Load.cpp",
        "folly/experimental/hazptr/hazptr.cpp",
        "folly/experimental/hazptr/memory_resource.cpp",
        "folly/experimental/io/FsUtil.cpp",
        "folly/experimental/io/HugePages.cpp",
        "folly/experimental/observer/detail/Core.cpp",
        "folly/experimental/observer/detail/ObserverManager.cpp",
        "folly/fibers/Baton.cpp",
        "folly/fibers/Fiber.cpp",
        "folly/fibers/FiberManager.cpp",
        "folly/fibers/FiberManagerMap.cpp",
        "folly/fibers/GuardPageAllocator.cpp",
        "folly/fibers/Semaphore.cpp",
        "folly/fibers/TimeoutController.cpp",
        "folly/fibers/detail/AtomicBatchDispatcher.cpp",
        "folly/futures/Barrier.cpp",
        "folly/futures/Future.cpp",
        "folly/futures/FutureException.cpp",
        "folly/futures/ManualExecutor.cpp",
        "folly/futures/QueuedImmediateExecutor.cpp",
        "folly/futures/ThreadWheelTimekeeper.cpp",
        "folly/hash/SpookyHashV1.cpp",
        "folly/hash/SpookyHashV2.cpp",
        "folly/init/Init.cpp",
        "folly/io/Compression.cpp",
        "folly/io/Cursor.cpp",
        "folly/io/IOBuf.cpp",
        "folly/io/IOBufQueue.cpp",
        "folly/io/RecordIO.cpp",
        "folly/io/ShutdownSocketSet.cpp",
        "folly/io/async/AsyncPipe.cpp",
        "folly/io/async/AsyncTimeout.cpp",
        "folly/io/async/AsyncUDPSocket.cpp",
        "folly/io/async/AsyncServerSocket.cpp",
        "folly/io/async/AsyncSignalHandler.cpp",
        "folly/io/async/AsyncSocket.cpp",
        "folly/io/async/AsyncSSLSocket.cpp",
        "folly/io/async/EventBase.cpp",
        "folly/io/async/EventBaseLocal.cpp",
        "folly/io/async/EventBaseManager.cpp",
        "folly/io/async/EventBaseThread.cpp",
        "folly/io/async/EventHandler.cpp",
        "folly/io/async/Request.cpp",
        "folly/io/async/SSLContext.cpp",
        "folly/io/async/SSLOptions.cpp",
        "folly/io/async/ScopedEventBaseThread.cpp",
        "folly/io/async/VirtualEventBase.cpp",
        "folly/io/async/HHWheelTimer.cpp",
        "folly/io/async/TimeoutManager.cpp",
        "folly/io/async/ssl/OpenSSLUtils.cpp",
        "folly/io/async/ssl/SSLErrors.cpp",
        "folly/io/compression/Zlib.cpp",
        "folly/json.cpp",
        "folly/portability/Dirent.cpp",
        "folly/portability/Fcntl.cpp",
        "folly/portability/Libgen.cpp",
        "folly/portability/Malloc.cpp",
        "folly/portability/Memory.cpp",
        "folly/portability/OpenSSL.cpp",
        "folly/portability/PThread.cpp",
        "folly/portability/Sockets.cpp",
        "folly/portability/Stdio.cpp",
        "folly/portability/Stdlib.cpp",
        "folly/portability/String.cpp",
        "folly/portability/SysFile.cpp",
        "folly/portability/SysMembarrier.cpp",
        "folly/portability/SysMman.cpp",
        "folly/portability/SysResource.cpp",
        "folly/portability/SysStat.cpp",
        "folly/portability/SysTime.cpp",
        "folly/portability/SysUio.cpp",
        "folly/portability/Time.cpp",
        "folly/portability/Unistd.cpp",
        "folly/ssl/Init.cpp",
        "folly/ssl/OpenSSLCertUtils.cpp",
        "folly/ssl/OpenSSLHash.cpp",
        "folly/ssl/detail/OpenSSLThreading.cpp",
        "folly/ssl/detail/SSLSessionImpl.cpp",
        "folly/stats/BucketedTimeSeries.cpp",
        "folly/stats/Histogram.cpp",
        "folly/stats/MultiLevelTimeSeries.cpp",
        "folly/stats/TimeseriesHistogram.cpp",
    ],
    copts = folly_copts,
    linkopts = [
        "-ldl",
        "-lm",
        "-lpthread",
    ],
    deps = [
        ":base",
        "@boost//:context",
        "@boost//:filesystem",
        "@boost//:regex",
        "@boost//:multi_index",
        "@boost//:function_types",
        "@boost//:program_options",
        "@libevent//:libevent",
        "@com_github_gflags_gflags//:gflags",
        "@snappy//:snappy",
        "@zlib//:zlib",
        "@openssl//:ssl",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "AsciiCaseInsensitiveTest",
    size = "small",
    srcs = [
        "folly/test/AsciiCaseInsensitiveTest.cpp"
    ],
    deps = [
        ":folly",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_googletest//:gtest_main",
    ]
)

