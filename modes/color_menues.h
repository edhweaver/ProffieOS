#ifndef MODE_COLOR_MENUES_H
#define MODE_COLOR_MENUES_H

#include "mode.h"
#include "../common/color.h"
#include "style_argument_helpers.h"
<<<<<<< HEAD
=======
#include "menu_list.h"
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e

namespace mode {

// Note, the currently edited color is stored in ShowColorStyle.
  
template<class SPEC>
struct HSLMode : public SPEC::SmoothMode {
public:
<<<<<<< HEAD
  void activate(bool onreturn) override {
    SPEC::SmoothMode::activate(onreturn);
=======
  void mode_activate(bool onreturn) override {
    SPEC::SmoothMode::mode_activate(onreturn);
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
    getSL<SPEC>()->SayRotate();
    hsl_color = ShowColorStyle::getColor().toHSL();
  }

  HSL hsl_color;
};

template<class SPEC>
struct ColorHueMode : public SPEC::HSLMode {
public:
  int get() override {
    return this->hsl_color.H * 32767.0;
  }

  void set(int x) override {
    // Say number??
    this->hsl_color.H = x / 32767.0;
    ShowColorStyle::SetColor(Color16(this->hsl_color));
  }
};

#ifndef COLOR_MENU_GAMMA
#define COLOR_MENU_GAMMA 2.2
#endif

template<class SPEC>
struct ColorBrightnessMode : public SPEC::HSLMode {
public:
  int get() override {
<<<<<<< HEAD
    return this->hsl_color.L;
=======
    float ret = this->hsl_color.L;
    if (ret > 0.5) {
      ret = powf((this->hsl_color.L - 0.5) * 2.0, COLOR_MENU_GAMMA) / 2.0 + 0.5;
    }
    return ret * 32768.0;
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
  }

  void set(int x) override {
    this->hsl_color.L = x / 32767.0;
    if (this->hsl_color.L > 0.5) {
<<<<<<< HEAD
      this->hsl_color.L = pow( (this->hsl_color.L - 0.5) * 2.0, 1.0/COLOR_MENU_GAMMA) / 2.0 + 0.5;
=======
      this->hsl_color.L = powf( (this->hsl_color.L - 0.5) * 2.0, 1.0/COLOR_MENU_GAMMA) / 2.0 + 0.5;
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
      this->hsl_color.S = 1.0;
    } else {
      this->hsl_color.S = this->hsl_color.L * 2.0f;
    }
    ShowColorStyle::SetColor(Color16(this->hsl_color));
  }
};

template<class SPEC>
struct ColorGammaMode : public SPEC::SmoothMode {
<<<<<<< HEAD
  uint16_t* value() = 0;
  void activate(bool onreturn) override {
    SPEC::SmoothMode::activate(onreturn);
=======
  virtual uint16_t* value() = 0;
  void mode_activate(bool onreturn) override {
    SPEC::SmoothMode::mode_activate(onreturn);
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
    getSL<SPEC>()->SayRotate();
  }
  int get() override {
    return powf(*value() / 65535.0, COLOR_MENU_GAMMA) * 32767;
  }

  void set(int x) override {
    *value()= powf(x / 32767.0, 1.0/COLOR_MENU_GAMMA) * 65535.0;
  }
};

template<class SPEC>
struct ColorRedMode : public SPEC::GammaMode {
  uint16_t* value() override { return &ShowColorStyle::getColor().r; }
};

template<class SPEC>
struct ColorGreenMode : public SPEC::GammaMode {
  uint16_t* value() override { return &ShowColorStyle::getColor().g; }
};

template<class SPEC>
struct ColorBlueMode : public SPEC::GammaMode {
  uint16_t* value() override { return &ShowColorStyle::getColor().b; }
};

<<<<<<< HEAD
template<class SPEC, class MENU>
struct SaveColorMenuEntry : public MenuEntry {
  void say(int entry) override {
    getSL<SPEC>->SaySave();
=======
Color16 menu_selected_color;

template<class SPEC>
struct SelectColorEntry : public MenuEntry {
  void say(int entry) override {
    getSL<SPEC>()->SaySelectColor();
  }
  void select(int entry) override {
    getSL<SPEC>()->SaySelect();
    menu_selected_color = ShowColorStyle::getColor();
  }
};
  
template<class SPEC>
struct UseSelectedColorEntry : public MenuEntry {
  void say(int entry) override {
    getSL<SPEC>()->SayUseSelectedColor();
  }
  void select(int entry) override {
    getSL<SPEC>()->SaySelect();
    ShowColorStyle::SetColor(menu_selected_color);
  }
};

template<class SPEC>
struct ResetColorToDefaultEntry : public MenuEntry {
  void say(int entry) override {
    getSL<SPEC>()->SayResetToDefaultColor();
  }
  void select(int entry) override {
    getSL<SPEC>()->SaySelect();
    LSPtr<char> builtin = style_parser.ResetArguments(GetStyle(menu_current_blade));
    char argspace[32];
    style_parser.GetArgument(builtin.get(), menu_current_arg, argspace);
    char* tmp;
    int r = strtol(argspace, &tmp, 0);
    int g = strtol(tmp+1, &tmp, 0);
    int b = strtol(tmp+1, NULL, 0);
    ShowColorStyle::SetColor(Color16(r,g,b));
  }
};

template<class SPEC, class MENU>
struct SaveColorMenuEntry : public MenuEntry {
  void say(int entry) override {
    getSL<SPEC>()->SaySave();
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
  }
  void select(int entry) override {
    getPtr<MENU>()->save();
  }
};

template<class SPEC, class MENU>
<<<<<<< HEAD
using ColorSelectList = typename SPEC::template MenuEntryMenu<
  SubMenuEntry<typename SPEC::ColorHueMode, typename SPEC::SoundLibrary::tAdjustColorHue>,
  SubMenuEntry<typename SPEC::ColorBrightnessMode, typename SPEC::SoundLibrary::tEditBrightNess>,
  SubMenuEntry<typename SPEC::ColorRedMode, typename SPEC::SoundLibrary::tRed>,
  SubMenuEntry<typename SPEC::ColorGreenMode, typename SPEC::SoundLibrary::tGreen>,
  SubMenuEntry<typename SPEC::ColorBlueMode, typename SPEC::SoundLibrary::tBlue>,
=======
using ColorSelectList = MenuEntryMenu<SPEC,
  SubMenuEntry<typename SPEC::ColorHueMode, typename SPEC::SoundLibrary::tAdjustColorHue>,
  SubMenuEntry<typename SPEC::ColorBrightnessMode, typename SPEC::SoundLibrary::tEditBrightness>,
  SubMenuEntry<typename SPEC::ColorRedMode, typename SPEC::SoundLibrary::tAdjustRed>,
  SubMenuEntry<typename SPEC::ColorGreenMode, typename SPEC::SoundLibrary::tAdjustGreen>,
  SubMenuEntry<typename SPEC::ColorBlueMode, typename SPEC::SoundLibrary::tAdjustBlue>,
  typename SPEC::SelectColorEntry,
  typename SPEC::UseSelectedColorEntry,
  typename SPEC::ResetColorToDefaultEntry,
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
  SaveColorMenuEntry<SPEC, MENU>>;

template<class SPEC>
struct ColorSelectMode : public ColorSelectList<SPEC, ColorSelectMode<SPEC>> {

  virtual void load() {
    ShowColorStyle::SetColor(GetColorArg(menu_current_blade, menu_current_arg));
  }

  virtual void save() {
    SetColorArg(menu_current_blade, menu_current_arg, ShowColorStyle::getColor());
  }

  void mode_activate(bool onreturn) override {
    if (!onreturn) {
      load();
      show_color_all_.Start();
    }
<<<<<<< HEAD
    ColorSelectList<SPEC, ColorSelectMode<SPEC>>::activate(onreturn);
=======
    ColorSelectList<SPEC, ColorSelectMode<SPEC>>::mode_activate(onreturn);
>>>>>>> 7e0c592331908007b0b4acbf2a0438c3a2eb579e
  }

  virtual void mode_exit() {
    show_color_all_.Stop();
    ColorSelectList<SPEC, ColorSelectMode<SPEC>>::exit();
  }

  ShowColorAllBladesTemplate<ShowColorStyle> show_color_all_;
};

}  // namespace mode

#endif
