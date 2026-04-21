Update a bundled C library submodule to a new version and apply all required changes.

Arguments: `$ARGUMENTS` — `libmongoc <version>` or `libmongocrypt <version>`, e.g. `libmongocrypt 1.17.3`

This command only applies to `src/libmongoc` and `src/libmongocrypt`. Other submodules are updated automatically by Dependabot.

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

### 2. Review the changelog

Check what changed between the old and new version:
- libmongoc: `https://github.com/mongodb/mongo-c-driver/releases/tag/<version>`
- libmongocrypt: `https://github.com/mongodb/libmongocrypt/releases/tag/<version>`

### 3. Regenerate source lists

```bash
php scripts/update-submodule-sources.php
```

This updates `config.m4` and `config.w32` with the current list of C source files.

### 4. Update version references

For **libmongoc** (`bson2` and `mongoc2` are both bundled in `src/libmongoc`):
```bash
sed -i '' 's|PHP_MONGODB_MIN_LIBBSON_VERSION=.*|PHP_MONGODB_MIN_LIBBSON_VERSION="<version>"|' config.m4
sed -i '' 's|PHP_MONGODB_MIN_LIBMONGOC_VERSION=.*|PHP_MONGODB_MIN_LIBMONGOC_VERSION="<version>"|' config.m4
sed -i '' 's|LIBMONGOC_VERSION: .*|LIBMONGOC_VERSION: "<version>"|' .github/workflows/tests.yml
```

For **libmongocrypt**:
```bash
sed -i '' 's|PHP_MONGODB_MIN_LIBMONGOCRYPT_VERSION=.*|PHP_MONGODB_MIN_LIBMONGOCRYPT_VERSION="<version>"|' config.m4
sed -i '' 's|LIBMONGOCRYPT_VERSION: .*|LIBMONGOCRYPT_VERSION: "<version>"|' .github/workflows/tests.yml
echo "<version>" > src/LIBMONGOCRYPT_VERSION_CURRENT
```

### 5. Update the SBOM

The SBOM requires Docker.
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
