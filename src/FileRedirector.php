<?php

namespace lucatume\WPBrowser\FileRedirection;

use FFI;
use FFI\CData;

class FileRedirector
{
    private const ZEND_HANDLE_STREAM = 3;
    private static bool $did_init = false;
    private static FFI $ffi;
    /**
     * @var array<string,string>
     */
    private array $fileRedirctionMap;

    public function __construct(private bool $shouldRedirectFiles)
    {
    }

    public function init(): void
    {
        if (self::$did_init) {
            return;
        }

        self::$did_init = true;

        $ffi = FFI::load(__DIR__ . '/php.h');

        $ffi->zend_stream_open_function = function ($filename, $handle) {
            $handle->type = self::ZEND_HANDLE_STREAM;
            // We are using isatty to be able to read each char of the file and
            // append the open tag if necessary
            $handle->handle->stream->isatty = 1;

            if ($this->shouldRedirectFiles) {
                $openPath = $this->getOpenedPathForFile($filename);
                $handle->opened_path = $this->getStringZendValue($openPath);
            }

            $file = fopen($filename, 'rb');

            $handle->handle->stream->reader = function ($handle, $buf, $sizeOfBuf) use ($file) {
                $char = fread($file, $sizeOfBuf);

                if (feof($file)) {
                    return false;
                }

                FFI::memcpy($buf, $char, $sizeOfBuf);

                return true;
            };
        };

        self::$ffi = $ffi;
    }

    private function getStringZendValue(string $stringValue): CData
    {
        $ex = self::$ffi->zend_rebuild_symbol_table();
        $sym = self::$ffi->zend_array_dup($ex);

        return $sym->arData->val->value->str;
    }

    public function getOpenedPathForFile(string $filename): string
    {
        foreach ($this->fileRedirctionMap as $fromFilePattern => $toFilePattern) {
            if (preg_match($fromFilePattern, $filename)) {
                return preg_replace($fromFilePattern, $toFilePattern, $filename);
            }
        }

        return $filename;
    }

    public function setFileRedirectionMap(array $fileRedirections): void
    {
        $this->fileRedirctionMap = $fileRedirections;
    }

    public function getFileRedirectionMap(): array
    {
        return $this->fileRedirctionMap;
    }
}
