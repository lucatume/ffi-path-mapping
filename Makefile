build:
	docker compose build
	DOCKER_PWD="$(shell pwd)" DOCKER_UID="$$(id -u)" DOCKER_GID="$$(id -g)" PROJECT_DIR="$$(pwd)" docker compose up -d
shell:
	DOCKER_PWD="$(shell pwd)" DOCKER_UID="$$(id -u)" DOCKER_GID="$$(id -g)" PROJECT_DIR="$$(pwd)" docker compose exec -it php-fpm sh
down:
	DOCKER_PWD="$(shell pwd)" DOCKER_UID="$$(id -u)" DOCKER_GID="$$(id -g)" PROJECT_DIR="$$(pwd)" docker compose down
xdebug_logs:
	docker compose exec -it php-fpm tail -f /tmp/xdebug.log
