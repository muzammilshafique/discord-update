# discord-update

A Linux package that helps resolve the Discord update issue.

## Installation

1. Download the latest release file from the [Releases](https://github.com/muzammilshafique/discord-update/releases) page.

2. Move the downloaded file to `/usr/bin`:

```bash
sudo mv update-discord /usr/bin/
```

3. Make the script executable (if necessary):

```bash
sudo chmod +x /usr/bin/update-discord
```

4. Run the update script to check the version:

```bash
sudo update-discord
```

5. Launch Discord as usual.

---

## Build from Source

If you prefer to build the program yourself:

1. Obtain the `update-discord.c` source file.

2. Ensure you have `gcc` and `cjson` installed. To install `cjson`:

```bash
sudo apt-get install libjson-c-dev
```

3. Compile the program:

```bash
gcc -o update-discord update-discord.c -I/usr/include/cjson -lcjson
```

4. Move the compiled binary to `/usr/bin`:

```bash
sudo mv update-discord /usr/bin/
```

5. Run the updater with:

```bash
sudo update-discord
```
