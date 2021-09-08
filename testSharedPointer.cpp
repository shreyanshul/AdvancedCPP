#include<iostream>
#include<memory>

struct Thing;
void some_api(const std::shared_ptr<Thing>& tp);

void some_api(const std::shared_ptr<Thing>& tp){
    std::cout <<"Count of sp from some_api = " << tp.use_count() << std::endl;
    return;
}

struct Thing : std::enable_shared_from_this<Thing> {
    void method() {
        some_api(shared_from_this());
    }
};

std::weak_ptr<Thing> foo() {
    auto sp = std::make_shared<Thing>();
    std::weak_ptr<Thing> wp2;
    {
        std::cout << "Initial count of sp = " << sp.use_count() << std::endl;

        sp->method();
        std::cout << "Count of sp after shared_from_this = " << sp.use_count() << std::endl;

        auto sp2 = sp;
        std::cout<<"Count after creating new ref to sp = " << sp.use_count() << std::endl;

        auto myLambda =([=]() {
            std::cout<<"Inside lambda count of sp = " << sp.use_count() << std::endl;
            return;
        });
	std::cout << "After lambda creation, count of sp = " << sp.use_count() << std::endl;
        std::cout << "Assigning a weak pointer to sp" << std:: endl;
        std::weak_ptr<Thing> wp = sp;
	wp2 = wp;
        std::cout << sp.use_count() << std::endl;
    }
    std::cout << sp.use_count() << std::endl;
    return wp2;
}

int main(){
	std::weak_ptr<Thing> wpm = foo();
	std::cout << "Crashing count = " << wpm.use_count();
	//wpm->method();
}
