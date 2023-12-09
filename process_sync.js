define X = 6;
define Y = 7;
semaphore pot = 1;
semaphore pot_is_empty = 0;
semaphore help1 = 0;
semaphore help2 = 0;
semaphore beans = 0;
semaphore carrots = 0;
semaphore mutex = 1;
shared int food = X + 5;
semaphore mutex2 = 1;
shared int beans_count = 0;


Διεργασία-Συνδαιτημόνας

repeat
    down(mutex);
    if (food>0) then 
        food--;
        if (food==0) up(pot_is_empty);
        up(mutex);
        down(pot);
        take_food();
        up(pot);
    else up(mutex);
forever;


Διεργασία-Μάγειρας

repeat
    down(pot_is_empty);
    up(help2);
    count = Y + 3;
    repeat
        down(mutex2);
        if (beans_count < Y+3)
            up(mutex2);
            up(help1);
            down(beans);
        else 
            up(mutex2); 
            break;
    forever;
    down(carrots);
    cook_food();
    down(mutex);
    food = X + 5;
    up(mutex);
    up(pot);
forever;


Διεργασία-βοηθός1

repeat
    down(help1);
    helper();
    down(mutex2);
    beans_count = beans_count + Y;
    up(mutex2);
    up(beans);
forever;


Διεργασία-βοηθός2

repeat
    down(help2);
    helper();
    up(carrots);
forever;