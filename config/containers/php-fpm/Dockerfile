ARG PHP_VERSION=8.0.11
FROM php:${PHP_VERSION}-fpm-alpine
ARG FIXUID=1000
ARG FIXGID=1000
RUN curl -sSL https://github.com/mlocati/docker-php-extension-installer/releases/latest/download/install-php-extensions -o - | sh -s \
          xdebug mysqli pdo_mysql ffi
# fixuid on /var/www/html
RUN addgroup -g ${FIXGID} docker && \
    adduser -u ${FIXUID} -G docker -h /home/docker -s /bin/sh -D docker \
    USER=docker && \
    GROUP=docker && \
    curl -SsL https://github.com/boxboat/fixuid/releases/download/v0.5.1/fixuid-0.5.1-linux-amd64.tar.gz | tar -C /usr/local/bin -xzf - && \
    chown root:root /usr/local/bin/fixuid && \
    chmod 4755 /usr/local/bin/fixuid && \
    mkdir -p /etc/fixuid
COPY ./fixuid.yml /etc/fixuid/config.yml
COPY ./php.ini /usr/local/etc/php/conf.d/user-php-ext.ini
COPY ./entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh
USER docker:docker
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
