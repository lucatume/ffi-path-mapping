<?php

if(!function_exists('xdebug_set_source_map')){
    return;
}

xdebug_set_source_map(__DIR__ . '/source-map.txt');
