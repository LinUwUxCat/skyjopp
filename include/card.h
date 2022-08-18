class card{
    private:
        bool enabled; //does the card count towards the player's score. This only works if the card is in a player's hand.
        int value; //-2 to 12
        bool facing; //true if up, false if down. when in stack, false.

    public:
        card(){
            this->value = -3;
            this->enabled = true;
            this->facing = false;
        }
        card(int value){
            this->value = value;
            this->enabled = true;
            this->facing = false;
        };
        bool flip(){
            facing = true;
            return facing;
        }
        void disable(){
            enabled = false;
        };
        int getValue(){ return value; };
        bool getFacing(){ return facing; };
        bool getEnabled(){ return enabled; };
        void setValue(int value){ this->value = value; };
        char* getColor(){
            if (this->value < 0){
                return "\033[38;5;21m";
            } else if (this->value == 0){
                return "\033[38;5;44m";
            } else if (this->value < 5){
                return "\033[38;5;46m";
            } else if (this->value < 9){
                return "\033[38;5;190m";
            } else {
                return "\033[38;5;196m";
            }
        }
};