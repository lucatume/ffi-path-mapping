Proof of concept path-mapping free setup

## Usage

Start the container providing the required user and local project directory information:
```
docker compose build
UID="$(id -u)" GID="$(id -g)" PROJECT_DIR="$(pwd)" docker compose up
```
In your IDE, start listening for XDebug connections on port `9003`.
Do not set up any path mappings.
Add a breakpoint at line `5` of the `src/source-1.php` file.

### No path mappings required (not working)
* Ensure there are no path mappings set up in your IDE.
* Visit `http://localhost:8923/?redirect_files=1`
* You should **not** get a prompt to set up path mappings, XDebug should just work.

### With path mappings (working)
* Ensure there are no path mappings set up in your IDE.
* Visit `http://localhost:8923`
* You should get a prompt to set up path mappings; once that is done, XDebug should work.
