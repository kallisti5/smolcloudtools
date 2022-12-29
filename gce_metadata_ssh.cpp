/* Copyright 2022, Alexander von Gluck IV <kallisti5@unixzen.com>
 * Released under the terms of the MIT license.
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <vector>


#define GCE_METADATA_BASE "http://metadata.google.internal/computeMetadata/v1/"


size_t
curl_write(void* ptr, size_t size, size_t members, std::string* s)
{
		s->append(static_cast<char*>(ptr), size * members);
		return size * members;
}


char*
get_metadata_keys(char* username)
{
		CURL* curl;
		CURLcode res;
		struct curl_slist *headers = NULL;

		std::string result;
		char url[128];
		snprintf(url, sizeof(url) - 1, "%s%s", GCE_METADATA_BASE, "instance/attributes/ssh-keys");

		curl = curl_easy_init();
		if (curl) {
				headers = curl_slist_append(headers, "Metadata-Flavor: Google");

				curl_easy_setopt(curl, CURLOPT_URL, url);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
				res = curl_easy_perform(curl);
				curl_easy_cleanup(curl);
				curl_slist_free_all(headers);

				// XXX: There's probably a better way to do this...
				std::istringstream stream(result);
				std::string line;
				while (std::getline(stream, line)) {
						std::string user = line.substr(0, line.find(':'));
						std::string key = line.substr(line.find(':') + 1);
						if (user == username)
							std::cout << key << "\n";
				}
		}
		return NULL;
}


int
main(int argc, char** argv)
{
		if (argc != 2) {
				printf("usage: %s <username>\n", argv[0]);
				return 1;
		}

		get_metadata_keys(argv[1]);
		return 0;
}

