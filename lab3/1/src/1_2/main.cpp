#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
    explicit MakeLemon(unsigned quantity)
            :m_quantity(quantity)
    {}

    auto operator()(IBeveragePtr && beverage)const
    {
        return make_unique<CLemon>(std::move(beverage), m_quantity);
    }
private:
    unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
    return [] (IBeveragePtr && b) {
        return make_unique<CCinnamon>(std::move(b));
    };
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона:
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
    // Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
    // Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
    // конструктору декоратора через make_unique
    return [=](auto && b) {
        // Функции make_unique передаем b вместе со списком аргументов внешней функции
        return make_unique<Condiment>(std::forward<decltype(b)>(b), args...);
    };
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
					<< MakeCondimentA(d, e, f)
					<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
	auto beverage =
		make_unique<CConcreteBeverage>(a, b, c)
		<< MakeCondimentA(d, e, f)
		<< MakeCondimentB(g, h);
или даже так:
	auto beverage =
		make_unique<CConcreteBeverage>
		<< MakeCondiment<CondimentA>(d, e, f)
		<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
	auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
	auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
	auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
	auto beverage = make_unique<CCondimentB>(
						make_unique<CCondimentA>(
							make_unique<CConcreteBeverage>(a, b, c), // Напиток
							d, e, f	// доп. параметы CondimentA
						),
						g, h		// доп. параметры CondimentB
					);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
	return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
	return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
    return decorate(std::forward<Component>(component));
}

bool CompleteBeverageChoice(unique_ptr<IBeverage> &beverage, int beverageChoice)
{
    switch (beverageChoice)
    {
        case 1:
            beverage = make_unique<CCoffee>();
            return true;
        case 2:
            cout << "Choose Cappuccino portion (1 - Standard, 2 - Double): ";
            int cappuccinoChoice;

            cin >> cappuccinoChoice;
            if (cappuccinoChoice > 4 or cappuccinoChoice < 1)
            {
                cout << "Invalid Cappuccino portion choice";
                return false;
            }

            beverage = make_unique<CCappuccino>(cappuccinoChoice == 2);
            return true;
        case 3:
            cout << "Choose Latte portion (1 - Standard, 2 - Double): ";
            
            int latteChoice;
            cin >> latteChoice;
            
            if (latteChoice > 4 or latteChoice < 1)
            {
                cout << "Invalid Latte portion choice";
                return false;
            }
            
            beverage = make_unique<CLatte>(latteChoice == 2);
            return true;
        case 4:
        {
            cout << "Choose tea type (1 - Black, 2 - Green, 3 - Red): ";

            int teaChoice;
            cin >> teaChoice;

            if (teaChoice > 4 or teaChoice < 1)
            {
                cout << "Invalid tea type choice";
                return false;
            }

            auto teaType = static_cast<TeaType>(teaChoice - 1);
            beverage = make_unique<CTea>(teaType);
            return true;
        }
        case 5:
        {
            cout << "Choose milkshake size (1 - Small, 2 - Medium, 3 - Large): ";

            int sizeChoice;
            cin >> sizeChoice;

            if (sizeChoice > 3 or sizeChoice < 1)
            {
                cout << "Invalid size milkshake choice";
                return false;
            }

            beverage = make_unique<CMilkshake>(static_cast<MilkshakeSizeType>(sizeChoice - 1));
            return true;
        }
        default:
            cout << "Invalid choice beverage" << endl;
            return false;
    }
}

bool CompleteCondimentChoice(unique_ptr<IBeverage> &beverage, int condimentChoice)
{
    switch (condimentChoice)
    {
        case 1:
            beverage = std::move(beverage) << MakeCondiment<CLemon>(2);
            return true;
        case 2:
            beverage = std::move(beverage) << MakeCondiment<CCinnamon>();
            return true;
        case 3:
            cout << "Choose Ice Cubes Type (1 - Water, 2 - Dry): ";
            int cubeChoice;
            cin >> cubeChoice;
            if (cubeChoice > 2 or cubeChoice < 1)
            {
                cout << "Invalid choice, try again)";
                return false;
            }
            beverage = std::move(beverage) << MakeCondiment<CIceCubes>
                    (2, cubeChoice == 1 ? IceCubeType::Water : IceCubeType::Dry);
            return true;
        case 4:
            beverage = std::move(beverage) << MakeCondiment<CChocolateCrumbs>(5);
            return true;
        case 5:
            beverage = std::move(beverage) << MakeCondiment<CCoconutFlakes>(5);
            return true;
        case 6:
            cout << "Choose Syrup Type (1 - Maple, 2 - Chocolate): ";
            int syrupChoice;

            cin >> syrupChoice;
            if (syrupChoice > 2 or syrupChoice < 1)
            {
                cout << "Invalid Syrup Type choice";
                return false;
            }

            beverage = std::move(beverage) << MakeCondiment<CSyrup>
                    (syrupChoice == 1 ? SyrupType::Maple : SyrupType::Chocolate);
            return true;
        case 7:
            beverage = std::move(beverage) << MakeCondiment<CCream>();
            return true;
        case 8:
            cout << "Choose Liquor Type (1 - Chocolate, 2 - Nutty): ";
            int liquorChoice;

            cin >> liquorChoice;
            if (liquorChoice > 2 or liquorChoice < 1)
            {
                cout << "Invalid choice Liquor Type";
                return false;
            }

            beverage = std::move(beverage) << MakeCondiment<CLiquor>
                    (liquorChoice == 1 ? LiquorType::CHOCOLATE : LiquorType::NUTTY);
            return true;
        case 9:
            cout << "Choose count slices max 5: ";
            int slices;

            cin >> slices;
            try
            {
                beverage = std::move(beverage) << MakeCondiment<CChocolate>(slices);
            }
            catch (const std::invalid_argument& e)
            {
                cout << e.what() << std::endl;
                return false;
            }

            return true;
        case 0:
            cout << "Break" << endl;
            cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
            return false;
        default:
            cout << "Invalid choice condiment" << endl;
            return true;
    }
}

void DialogWithUser()
{
    unique_ptr<IBeverage> beverage;

    cout << "Choose your base beverage:\n";
    cout << "1 - Coffee\n2 - Cappuccino\n3 - Latte\n4 - Tea\n5 - Milkshake\n";

    int beverageChoice;
    cin >> beverageChoice;

    if (CompleteBeverageChoice(beverage, beverageChoice))
    {
        while (true)
        {
            cout << "Choose your condiment:\n";
            cout << "1 - Lemon\n2 - Cinnamon\n3 - Ice Cubes\n4 - Chocolate Crumbs\n";
            cout << "5 - Coconut Flakes\n6 - Syrup\n";
            cout << "7 - Cream\n8 - Liquor\n9 - Chocolate\n";
            cout << "0 - Break\n";

            int condimentChoice;
            cin >> condimentChoice;

            if (!CompleteCondimentChoice(beverage, condimentChoice))
            {
                break;
            }
        }
    }
}

void DialogWithUserDeprecated()
{
    cout << "Type 1 for coffee or 2 for tea\n";
    int beverageChoice;
    cin >> beverageChoice;

    unique_ptr<IBeverage> beverage;

    if (beverageChoice == 1)
    {
        beverage = make_unique<CCoffee>();
    }
    else if (beverageChoice == 2)
    {
        beverage = make_unique<CTea>(TeaType::BLACK);
    }
    else
    {
        return;
    }

    int condimentChoice;
    for (;;)
    {
        cout << "1 - Lemon, 2 - Cinnamon, 0 - Checkout" << endl;
        cin >> condimentChoice;

        if (condimentChoice == 1)
        {
            //beverage = make_unique<CLemon>(move(beverage));
            beverage = move(beverage) << MakeCondiment<CLemon>(2);
        }
        else if (condimentChoice == 2)
        {
            //beverage = make_unique<CCinnamon>(move(beverage));
            beverage = move(beverage) << MakeCondiment<CCinnamon>();
        }
        else if (condimentChoice == 0)
        {
            break;
        }
        else
        {
            return;
        }
    }

    cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}


int main()
{
    DialogWithUser();
    cout << endl;
//    {
//        // Наливаем чашечку латте
//        auto latte = make_unique<CLatte>();
//        // добавляем корицы
//        auto cinnamon = make_unique<CCinnamon>(move(latte));
//        // добавляем пару долек лимона
//        auto lemon = make_unique<CLemon>(move(cinnamon), 2);
//        // добавляем пару кубиков льда
//        auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
//        // добавляем 2 грамма шоколадной крошки
//        auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);
//
//        // Выписываем счет покупателю
//        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
//    }
//
//    {
//        auto beverage =
//                make_unique<CChocolateCrumbs>(			// Внешний слой: шоколадная крошка
//                        make_unique<CIceCubes>(				// | под нею - кубики льда
//                                make_unique<CLemon>(			// | | еще ниже лимон
//                                        make_unique<CCinnamon>(		// | | | слоем ниже - корица
//                                                make_unique<CLatte>()),	// | | |   в самом сердце - Латте
//                                        2),							// | | 2 дольки лимона
//                                2, IceCubeType::Dry),			// | 2 кубика сухого льда
//                        2);									// 2 грамма шоколадной крошки
//
//        // Выписываем счет покупателю
//        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
//    }
//
//    // Подробнее рассмотрим работу MakeCondiment и оператора <<
//    {
//        // lemon - функция, добавляющая "2 дольки лимона" к любому напитку
//        auto lemon2 = MakeCondiment<CLemon>(2);
//        // iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
//        auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);
//
//        auto tea = make_unique<CTea>();
//
//        // декорируем чай двумя дольками лимона и тремя кусочками льда
//        auto lemonIceTea = iceCubes3(lemon2(move(tea)));
//        /* Предыдущая строка выполняет те же действия, что и следующий код:
//        auto lemonIceTea =
//            make_unique<CIceCubes>(
//                make_unique<CLemon>(
//                    move(tea),
//                    2),
//                2, IceCubeType::Water);
//        */
//
//        auto oneMoreLemonIceTea =
//                make_unique<CTea>()	// Берем чай
//                        << MakeCondiment<CLemon>(2)	// добавляем пару долек лимона
//                        << MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
//        /*
//        Предыдущая конструкция делает то же самое, что и следующая:
//        auto oneMoreLemonIceTea =
//            MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
//                MakeCondiment<CLemon>(2)(make_unique<CTea>())
//                );
//        */
//    }
//
//    // Аналог предыдущего решения с добавкой синтаксического сахара
//    // обеспечиваемого операторами << и функцией MakeCondiment
//    {
//        auto beverage =
//                make_unique<CLatte>()							// Наливаем чашечку латте,
//                        << MakeCondiment<CCinnamon>()					// оборачиваем корицей,
//                        << MakeCondiment<CLemon>(2)						// добавляем пару долек лимона
//                        << MakeCondiment<CIceCubes>(2, IceCubeType::Dry)// брасаем пару кубиков сухого льда
//                        << MakeCondiment<CChocolateCrumbs>(2);			// посыпаем шоколадной крошкой
//
//        // Выписываем счет покупателю
//        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
//    }
//
//    {
//        auto beverage =
//                make_unique<CMilkshake>()					// Наливаем молочный коктейль
//                        << MakeCondiment<CSyrup>(SyrupType::Maple)	// заливаем кленовым сиропом
//                        << MakeCondiment<CCoconutFlakes>(8);		// посыпаем кокосовой стружкой
//
//        // Выписываем счет покупателю
//        cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
//    }
}