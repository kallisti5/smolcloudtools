default: gce_metadata_ssh
CURL_FLAGS=$(shell pkg-config libcurl --libs)

gce_metadata_ssh: gce_metadata_ssh.cpp
	g++ $(CURL_FLAGS) -o $@ $^

clean: gce_metadata_ssh
	rm -f $^
