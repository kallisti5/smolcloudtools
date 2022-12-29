# Smol Cloud Tools

A collection of highly cross-platform bare minimum tools to assist in managing your cloud.

# Tools

## gce_metadata_ssh

A tiny utility designed to function with SSH's AuthorizedKeysCommand to allow user access
via Google's metadata SSH data.

This should only really be used on platforms where oslogin doesn't work as expected.
(a good example is Haiku not having PAM / NSS)

## Platform Support

* Linux
* Haiku
* BSD
