#!bin/bash

PLATFORMS=("linux/amd64")
OS_LIST=("ubuntu" "alpine")

if ! docker buildx ls | grep -q "multiarch"; then
    docker buildx create --name multiarch --driver docker-container --use
    docker buildx inspect --bootstrap
else
    docker buildx use multiarch
fi

for os in "${OS_LIST[@]}"; do
    for platform in "${PLATFORMS[@]}"; do
        platform_name=$(echo $platform | sed 's/\//-/g')
        image_name="s21_string-${platform_name}-${os}"

        echo "Testing $os on $platform"

        docker buildx build --platform $platform -f Dockerfile.$os -t $image_name --load .
        docker run --rm --platform $platform $image_name
    done
done

