#include <bangtal.h>
using namespace bangtal;


int main()
{

	auto scene1 = Scene::create("룸1", "./images/배경-1.png");
	auto scene2 = Scene::create("룸2", "./images/배경-2.png");
	auto scene3 = Scene::create("룸3", "./images/배경-2.png");




	auto key1 = Object::create("./images/열쇠.png", scene1, 600, 150);
	key1->setScale(0.2f);

	key1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key1->pick();

		return true;

		});

	auto key2 = Object::create("./images/열쇠2.png", scene1, 295, 220);
	key2->setScale(0.2f);

	
	auto box_opened = false;

	auto box = Object::create("./images/상자-닫힘.png", scene1, 295, 200);
	box->setScale(0.5f);
	box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (box_opened == false) {

			box->setImage("./images/상자-열림.png");
			box->setScale(0.5f);
			box_opened = true;
			key2->pick();


		}

		else {

		}

		return true;

		});
		
	auto  flowerpot_moved = false;
	auto flowerpot = Object::create("./images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (flowerpot_moved == false) {

			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved = true;


			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved = true;

			}

			return true;
		}

		});




	auto open1 = false;
	auto door1 = Object::create("./images/문-오른쪽-닫힘.png", scene1, 800, 270);


	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool{


		if (open1 == true) {	

			scene2->enter();

		}

		else if (key1->isHanded()) {
		
			showMessage("이 열쇠로는 열리지 않습니다");
				
		}

		else if (key2->isHanded()) {					

			door1->setImage("./images/문-오른쪽-열림.png");
			open1 = true;

		}

		else {
		
			showMessage("열쇠가 필요해!!!");

		}
		return true;
	});

	auto door2 = Object::create("./images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});


	auto door3_open = false, door3_locked = true;
	auto door3 = Object::create("./images/문-오른쪽-닫힘.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {


		if (door3_locked) {

			showMessage("문이 잠겨있다.");

		}

		else if (door3_open == true) {

			scene3->enter();

		}
		else {
			door3->setImage("./images/문-오른쪽-열림.png");
			door3_open = true;

		}

		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		door3_locked = false;
		showMessage("철커덕--");
		return true;

		});

	
	auto keypad = Object::create("./images/키패드.png", scene2, 885, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", door3);
		return true;
		});

	auto password = Object::create("./images/암호.png", scene2, 400, 100, false);


	auto lighted = true;
	auto button = Object::create("./images/스위치.png", scene2, 880, 440);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (lighted) {
			scene2->setLight(0.2f);
			password->show();
			lighted = false;

		}
		else {
		
			scene2->setLight(1.0f);
			password->hide();
			lighted = true;

		}
		return true;
		});

	auto door4 = Object::create("./images/문-왼쪽-열림.png", scene3, 320, 270);
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});



	auto door5_open = false, door5_locked = true;
	auto door5 = Object::create("./images/문-오른쪽-닫힘.png", scene3, 910, 270);
	door5->hide(); 
	

	auto chung = Object::create("./images/중.png", scene3, 300, 150);
	auto ang = Object::create("./images/앙.png", scene3, 300, 50);

	auto square2_right_moved = false;
	auto square2 = Object::create("./images/가운데.png", scene3, 250, 80);
	square2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (square2_right_moved == false) {

			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				square2->locate(scene3, 200, 50);


			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				square2->locate(scene3, 400, 120);
				square2_right_moved = true;

				if (square2_right_moved) {

					door5->show();
					door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

						if (door5_locked == false) {

							endGame();

						}

						else if (door5_locked == true && key1->isHanded()) {

							door5->setImage("./images/문-오른쪽-열림.png");
							door5_locked = false;

						}

						else {

							showMessage("열쇠가 필요해!!!");

						}
						return true;
						});
				}

			}



			return true;
		}

		});

	auto paper = Object::create("./images/쪽지.png", scene3, 600, 50);
	paper->setScale(0.1f);
	paper->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		paper->pick();
		return true;
		});




	startGame(scene1);

	return 0;
}