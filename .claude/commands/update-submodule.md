Update a bundled C library submodule to a new version and apply all required changes.

Arguments: `$ARGUMENTS` — `libmongoc <version>` or `libmongocrypt <version>`, e.g. `libmongocrypt 1.17.3`

Current state:
- libmongoc: !`cat src/libmongoc/VERSION_CURRENT 2>/dev/null || echo "(unknown)"`
- libmongocrypt: !`cat src/LIBMONGOCRYPT_VERSION_CURRENT 2>/dev/null || echo "(unknown)"`

## Steps to perform

### 1. Update the submodule pointer

Fetch tags and checkout the requested version tag:

```bash
git -C src/<submodule> fetch --tags
git -C src/<submodule> checkout <version>
```

Verify with `git submodule status src/<submodule>`.

### 2. Regenerate source lists

```bash
php scripts/update-submodule-sources.php
```

This updates `config.m4` and `config.w32` with the current list of C source files.

### 3. Update pkg-config version requirements in config.m4

Read `config.m4` and update the minimum version in the `PKG_CHECK_MODULES` call(s):

- **libmongoc**: update `bson2 >= X.Y.Z` and `mongoc2 >= X.Y.Z` (`bson2` and `mongoc2` are both bundled in the `src/libmongoc` submodule)
- **libmongocrypt**: update `libmongocrypt >= X.Y.Z`

Also update the corresponding `AC_MSG_ERROR` messages.

### 4. Update LIBMONGOCRYPT_VERSION_CURRENT (libmongocrypt only)

For libmongocrypt updates, update `src/LIBMONGOCRYPT_VERSION_CURRENT` with the new version string.

### 5. Update the SBOM

The SBOM requires Docker. Start colima if not running:

```bash
colima status 2>/dev/null | grep -q "Running" || colima start
```

Then generate the updated SBOM:

```bash
bash scripts/update-sbom.sh
```

This updates `sbom.json` using the versions in `src/libmongoc/VERSION_CURRENT` and `src/LIBMONGOCRYPT_VERSION_CURRENT`.

### 6. Commit

Stage and commit all changed files:

- `src/<submodule>` (submodule pointer)
- `config.m4` (source lists + version requirements)
- `config.w32` (source lists, if changed)
- `src/LIBMONGOCRYPT_VERSION_CURRENT` (libmongocrypt only)
- `sbom.json`

Commit message: `PHPC-XXXX Upgrade <submodule> to <version>`
