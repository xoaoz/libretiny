#!/usr/bin/env python3

import argparse
import io
import json
import tarfile
import urllib.request
from pathlib import Path


SDK_URL = (
    "https://github.com/ambiot/amb1_arduino/raw/master/"
    "Arduino_package/release/ameba_1-2.0.12-build20220509.tar.gz"
)
PACKAGE_NAME = "framework-realtek-amb1"
PACKAGE_VERSION = "2.0.12"


def read_archive(source: str) -> bytes:
    source_path = Path(source)
    if source_path.is_file():
        return source_path.read_bytes()
    with urllib.request.urlopen(source) as response:
        return response.read()


def build_package(source: str, output: Path) -> None:
    archive_data = read_archive(source)
    package_manifest = {
        "name": PACKAGE_NAME,
        "version": PACKAGE_VERSION,
        "description": "Realtek Ameba1 Arduino SDK for RTL8710AF",
        "keywords": ["framework", "arduino", "realtek", "rtl8710af"],
        "repository": {
            "type": "git",
            "url": "https://github.com/ambiot/amb1_arduino.git",
        },
        "license": "LGPL-2.1",
    }

    output.parent.mkdir(parents=True, exist_ok=True)
    with tarfile.open(output, "w:gz") as package:
        manifest_data = json.dumps(package_manifest, indent=2).encode("ascii")
        manifest = tarfile.TarInfo("package.json")
        manifest.size = len(manifest_data)
        package.addfile(manifest, io.BytesIO(manifest_data))

        with tarfile.open(fileobj=io.BytesIO(archive_data), mode="r:gz") as sdk:
            for member in sdk.getmembers():
                if not member.name.startswith("hardware/"):
                    continue
                member.name = "Arduino_package/" + member.name
                package.addfile(member, sdk.extractfile(member) if member.isfile() else None)

    with tarfile.open(output, "r:gz") as package:
        package_names = package.getnames()
        required_prefixes = (
            "Arduino_package/hardware/system/",
            "Arduino_package/hardware/variants/rtl8710/",
        )
        missing = [
            prefix
            for prefix in required_prefixes
            if not any(name.startswith(prefix) for name in package_names)
        ]
        if "package.json" not in package_names:
            missing.insert(0, "package.json")
        if missing:
            raise RuntimeError(f"Generated package is missing: {', '.join(missing)}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--source",
        default=SDK_URL,
        help="SDK archive path or URL (default: official Ameba1 archive)",
    )
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    build_package(args.source, args.output)


if __name__ == "__main__":
    main()