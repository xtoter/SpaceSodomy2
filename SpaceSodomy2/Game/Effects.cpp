#include "pch.h"
#include "Effects.h"


Effects::Effect::Effect() {
    duration.set_change_vel(-1);

}
Effects::Effect::Effect(Algebraic_Type _type) {
    type = _type;
    duration.set_change_vel(-1);

}
Effects::Effect::Effect(Counter counter, Algebraic_Type _type) {
    type = _type;
    duration = counter;
    duration.set_change_vel(-1);

}
Effects::Effect::Effect(float time, Algebraic_Type _type) {
    type = _type;
    duration = Counter(time);
    duration.set_change_vel(-1);

}

Effects::Algebraic_Type Effects::Effect::get_type() {
    return type;
}
Counter* Effects::Effect::get_counter() {
    return &duration;
}

void Effects::Effect::set_type(Algebraic_Type _type) {
    type = _type;
}


void Effects::Effect::set_counter(Counter counter) {
    duration = counter;
}

void Effects::Effect::step(float dt) {
    duration.step(dt);
}

Effects::Effect& Effects::Effect::operator+=(Effect other) {
    if (type == Algebraic_Type::ANNULATOR) {
        return *this;
    }

    //TO REMOVE LATER: FOR DEBUG
    if (type != other.type) {
        std::cout << "Error adding effects: Algebraic types are ";
        switch (type) {
        case Algebraic_Type::MAXIMAL:
            std::cout << "MAXIMAL ";
            break;
        case Algebraic_Type::ADDITIVE:
            std::cout << "ADDITIVE ";
            break;
        case Algebraic_Type::ANNULATOR:
            std::cout << "ANNULATOR ";
            break;
        }
        std::cout << "and ";
        switch (type) {
        case Algebraic_Type::MAXIMAL:
            std::cout << "MAXIMAL ";
            break;
        case Algebraic_Type::ADDITIVE:
            std::cout << "ADDITIVE ";
            break;
        case Algebraic_Type::ANNULATOR:
            std::cout << "ANNULATOR ";
            break;
        }
        std::cout << "\n";
    }


    if (other.duration.get() < b2_epsilon) {
        return *this;
    }
    switch (type) {
    case Algebraic_Type::MAXIMAL:
        duration.set(std::max(duration.get(), other.duration.get()));
        break;
    case Algebraic_Type::ADDITIVE:
        duration.modify(other.duration.get());
        break;
    }
    return *this;

}
Effects::Effect Effects::Effect::operator+(Effect effect) {
    auto left = *this;
    left += effect;
    return left;
}



Effects::Effects() : effects(Effects::Types::COUNT) {
}

Effects::Effects(Effects_Def* def) : effects(Effects::Types::COUNT) {
    for (int i = 0; i < def->effects.size(); i++) {
        effects[i] = (def->effects[i]);
    }
}
Effects::Effect* Effects::get_effect(Types type) {
    return &effects[type];
}
void Effects::set_effect(Effect* eff, Types type) {
    effects[type] = *eff;
}

void Effects::step(float dt) {
    for (int i = 0; i < Effects::Types::COUNT; i++) {
        effects[i].step(dt);
    }
}

void Effects::update(Effects_Def* _effects) {
    if (!_effects) {
        return;
    }
    for (int i = 0; i < Types::COUNT; i++) {
        effects[i] += _effects->effects[i];
    }
}


Effects_Def::Effects_Def() {
    for (int i = 0; i < Effects::Types::COUNT; i++) {
        Effects::Effect eff;
        effects.push_back(eff);
    }
}

Effects_Def::Effects_Def(Effects::Algebraic_Type type) {
    for (int i = 0; i < Effects::Types::COUNT; i++) {
        effects.push_back(Effects::Effect(type));
    }
}