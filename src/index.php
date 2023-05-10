<?php

$projectDir = getenv('PROJECT_DIR');
// $shouldRedirectFiles comes from the `?redirect_files=1` query string parameter.
$shouldRedirectFiles = $_GET['redirect_files'] ?? false;

use lucatume\WPBrowser\FileRedirection\FileRedirector;

require_once __DIR__ . '/FileRedirector.php';
$fileRedirector = new FileRedirector($shouldRedirectFiles);
$fileRedirector->setFileRedirectionMap([
    '#^' . preg_quote(__DIR__, '#') . '(\\/.*\\.php)$#' => $projectDir . '${1}'
]);

$fileRedirector->init();

include __DIR__ . '/source-1.php';
?>

<!DOCTYPE HTML>
<html>
<head>
    <meta charset="utf-8">
    <title>Test page</title>
</head>
<main>
    <p><?php
        echo 'Run value is ' . run(); ?></p>
</main>
<body>
</body>
</html>
