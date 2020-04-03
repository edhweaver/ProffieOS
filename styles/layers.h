#ifndef STYLES_LAYERS_H
#define STYLES_LAYERS_H

// Usage: Layers<BASE, LAYER1, LAYER2, ...>
// BASE: COLOR or LAYER
// LAYER1, LAYER2: LAYER
// return value: COLOR or LAYER (same as BASE)
// This style works like layers in gimp or photoshop.
// In most cases, the layers are expected to be normally transparent effects
// that turn opaque when then want to paint an effect over the base color.
// If the base color is opqaque, the final result of this style will also be
// opaque. If the base color is transparent, the final result may also be transparent,
// depending on what the layers paint on top of the base color.

template<class BASE, class... LAYERS> class Layers {};

template<class BASE, class L1>
class Layers<BASE, L1> {
public:
  bool run(BladeBase* blade) {
    layer_.run(blade);
    return RunStyle(&base_, blade);
  }
private:
  BASE base_;
  L1 layer_;
public:
  auto getColor(int led) -> decltype(base_.getColor(led) << layer_.getColor(led)) {
    return base_.getColor(led) << layer_.getColor(led);
  }

};

template<class BASE, class L1, class L2, class... LAYERS>
  class Layers<BASE, L1, L2, LAYERS...> : public Layers<Layers<BASE, L1>, L2, LAYERS...> {};

#endif