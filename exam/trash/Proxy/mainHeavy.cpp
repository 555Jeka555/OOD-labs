#include <iostream>
#include <memory>

class IResource {
public:
    virtual void load() = 0;
    virtual ~IResource() = default;
};

class HeavyResource : public IResource {
public:
    void load() override {
        std::cout << "Loading heavy resource..." << std::endl;
    }
};

class HeavyResourceProxy : public IResource {
private:
    std::unique_ptr<HeavyResource> resource;

public:
    void load() override {
        if (!resource) {
            std::cout << "Creating heavy resource..." << std::endl;
            resource = std::make_unique<HeavyResource>();
        }
        resource->load();
    }
};

int main() {
    HeavyResourceProxy proxy;

    std::cout << "First call to load:" << std::endl;
    proxy.load();

    std::cout << "\nSecond call to load:" << std::endl;
    proxy.load();

    return 0;
}