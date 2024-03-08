import { c as create_ssr_component, l as compute_rest_props, a as subscribe, f as createEventDispatcher, e as escape, b as add_attribute, i as each } from './ssr-V-Hd1H2_.js';
import { p as prefersReducedMotionStore } from './ProgressBar.svelte_svelte_type_style_lang--QH1TJfj.js';
import { f as fly, s as scale } from './index2-Jzlktigj.js';

const cBase = "textarea cursor-pointer";
const cChipWrapper = "space-y-4";
const cChipList = "flex flex-wrap gap-2";
const cInputField = "unstyled bg-transparent border-0 !ring-0 p-0 w-full";
const InputChip = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let classesInvalid;
  let classesBase;
  let classesChipWrapper;
  let classesChipList;
  let classesInput;
  let $$restProps = compute_rest_props($$props, [
    "input",
    "name",
    "value",
    "whitelist",
    "max",
    "minlength",
    "maxlength",
    "allowUpperCase",
    "allowDuplicates",
    "validation",
    "duration",
    "required",
    "chips",
    "invalid",
    "padding",
    "rounded",
    "regionChipWrapper",
    "regionChipList",
    "regionInput",
    "label",
    "transitions",
    "listTransitionIn",
    "listTransitionInParams",
    "listTransitionOut",
    "listTransitionOutParams",
    "chipTransitionIn",
    "chipTransitionInParams",
    "chipTransitionOut",
    "chipTransitionOutParams",
    "addChip",
    "removeChip"
  ]);
  let $prefersReducedMotionStore, $$unsubscribe_prefersReducedMotionStore;
  $$unsubscribe_prefersReducedMotionStore = subscribe(prefersReducedMotionStore, (value2) => $prefersReducedMotionStore = value2);
  const dispatch = createEventDispatcher();
  let { input = "" } = $$props;
  let { name } = $$props;
  let { value = [] } = $$props;
  let { whitelist = [] } = $$props;
  let { max = -1 } = $$props;
  let { minlength = -1 } = $$props;
  let { maxlength = -1 } = $$props;
  let { allowUpperCase = false } = $$props;
  let { allowDuplicates = false } = $$props;
  let { validation = () => true } = $$props;
  let { duration = 150 } = $$props;
  let { required = false } = $$props;
  let { chips = "variant-filled" } = $$props;
  let { invalid = "input-error" } = $$props;
  let { padding = "p-2" } = $$props;
  let { rounded = "rounded-container-token" } = $$props;
  let { regionChipWrapper = "" } = $$props;
  let { regionChipList = "" } = $$props;
  let { regionInput = "" } = $$props;
  let { label = "Chips select" } = $$props;
  let { transitions = !$prefersReducedMotionStore } = $$props;
  let { listTransitionIn = fly } = $$props;
  let { listTransitionInParams = { duration: 150, opacity: 0, y: -20 } } = $$props;
  let { listTransitionOut = fly } = $$props;
  let { listTransitionOutParams = { duration: 150, opacity: 0, y: -20 } } = $$props;
  let { chipTransitionIn = scale } = $$props;
  let { chipTransitionInParams = { duration: 150, opacity: 0 } } = $$props;
  let { chipTransitionOut = scale } = $$props;
  let { chipTransitionOutParams = { duration: 150, opacity: 0 } } = $$props;
  let inputValid = true;
  let chipValues = value?.map((val) => {
    return { val, id: Math.random() };
  }) || [];
  let selectElement;
  function validateCustom(chip) {
    return validation === void 0 || validation(chip);
  }
  function validateCount() {
    return max === -1 || value.length < max;
  }
  function validateLength(chip) {
    return (minlength === -1 || chip.length >= minlength) && (maxlength === -1 || chip.length <= maxlength);
  }
  function validateWhiteList(chip) {
    return whitelist.length === 0 || whitelist.includes(chip);
  }
  function validateDuplicates(chip) {
    return allowDuplicates || !value.includes(chip);
  }
  function validate(chip = "") {
    if (!chip && !input)
      return false;
    chip = chip !== "" ? chip.trim() : input.trim();
    return validateCustom(chip) && validateCount() && validateLength(chip) && validateWhiteList(chip) && validateDuplicates(chip);
  }
  function addChipCommon(chip) {
    chip = allowUpperCase ? chip : chip.toLowerCase();
    value.push(chip);
    value = value;
    chipValues.push({ val: chip, id: Math.random() });
    chipValues = chipValues;
  }
  function removeChipCommon(chip) {
    let chipIndex = value.indexOf(chip);
    value.splice(chipIndex, 1);
    value = value;
    chipValues.splice(chipIndex, 1);
    chipValues = chipValues;
  }
  function addChip(chip) {
    inputValid = validate(chip);
    if (inputValid === false) {
      dispatch("invalidManually", { input: chip });
      return;
    }
    addChipCommon(chip);
    dispatch("addManually", {
      chipIndex: value.length - 1,
      chipValue: chip
    });
  }
  function removeChip(chip) {
    if ($$restProps.disabled)
      return;
    removeChipCommon(chip);
    dispatch("removeManually", { chipValue: chip });
  }
  if ($$props.input === void 0 && $$bindings.input && input !== void 0)
    $$bindings.input(input);
  if ($$props.name === void 0 && $$bindings.name && name !== void 0)
    $$bindings.name(name);
  if ($$props.value === void 0 && $$bindings.value && value !== void 0)
    $$bindings.value(value);
  if ($$props.whitelist === void 0 && $$bindings.whitelist && whitelist !== void 0)
    $$bindings.whitelist(whitelist);
  if ($$props.max === void 0 && $$bindings.max && max !== void 0)
    $$bindings.max(max);
  if ($$props.minlength === void 0 && $$bindings.minlength && minlength !== void 0)
    $$bindings.minlength(minlength);
  if ($$props.maxlength === void 0 && $$bindings.maxlength && maxlength !== void 0)
    $$bindings.maxlength(maxlength);
  if ($$props.allowUpperCase === void 0 && $$bindings.allowUpperCase && allowUpperCase !== void 0)
    $$bindings.allowUpperCase(allowUpperCase);
  if ($$props.allowDuplicates === void 0 && $$bindings.allowDuplicates && allowDuplicates !== void 0)
    $$bindings.allowDuplicates(allowDuplicates);
  if ($$props.validation === void 0 && $$bindings.validation && validation !== void 0)
    $$bindings.validation(validation);
  if ($$props.duration === void 0 && $$bindings.duration && duration !== void 0)
    $$bindings.duration(duration);
  if ($$props.required === void 0 && $$bindings.required && required !== void 0)
    $$bindings.required(required);
  if ($$props.chips === void 0 && $$bindings.chips && chips !== void 0)
    $$bindings.chips(chips);
  if ($$props.invalid === void 0 && $$bindings.invalid && invalid !== void 0)
    $$bindings.invalid(invalid);
  if ($$props.padding === void 0 && $$bindings.padding && padding !== void 0)
    $$bindings.padding(padding);
  if ($$props.rounded === void 0 && $$bindings.rounded && rounded !== void 0)
    $$bindings.rounded(rounded);
  if ($$props.regionChipWrapper === void 0 && $$bindings.regionChipWrapper && regionChipWrapper !== void 0)
    $$bindings.regionChipWrapper(regionChipWrapper);
  if ($$props.regionChipList === void 0 && $$bindings.regionChipList && regionChipList !== void 0)
    $$bindings.regionChipList(regionChipList);
  if ($$props.regionInput === void 0 && $$bindings.regionInput && regionInput !== void 0)
    $$bindings.regionInput(regionInput);
  if ($$props.label === void 0 && $$bindings.label && label !== void 0)
    $$bindings.label(label);
  if ($$props.transitions === void 0 && $$bindings.transitions && transitions !== void 0)
    $$bindings.transitions(transitions);
  if ($$props.listTransitionIn === void 0 && $$bindings.listTransitionIn && listTransitionIn !== void 0)
    $$bindings.listTransitionIn(listTransitionIn);
  if ($$props.listTransitionInParams === void 0 && $$bindings.listTransitionInParams && listTransitionInParams !== void 0)
    $$bindings.listTransitionInParams(listTransitionInParams);
  if ($$props.listTransitionOut === void 0 && $$bindings.listTransitionOut && listTransitionOut !== void 0)
    $$bindings.listTransitionOut(listTransitionOut);
  if ($$props.listTransitionOutParams === void 0 && $$bindings.listTransitionOutParams && listTransitionOutParams !== void 0)
    $$bindings.listTransitionOutParams(listTransitionOutParams);
  if ($$props.chipTransitionIn === void 0 && $$bindings.chipTransitionIn && chipTransitionIn !== void 0)
    $$bindings.chipTransitionIn(chipTransitionIn);
  if ($$props.chipTransitionInParams === void 0 && $$bindings.chipTransitionInParams && chipTransitionInParams !== void 0)
    $$bindings.chipTransitionInParams(chipTransitionInParams);
  if ($$props.chipTransitionOut === void 0 && $$bindings.chipTransitionOut && chipTransitionOut !== void 0)
    $$bindings.chipTransitionOut(chipTransitionOut);
  if ($$props.chipTransitionOutParams === void 0 && $$bindings.chipTransitionOutParams && chipTransitionOutParams !== void 0)
    $$bindings.chipTransitionOutParams(chipTransitionOutParams);
  if ($$props.addChip === void 0 && $$bindings.addChip && addChip !== void 0)
    $$bindings.addChip(addChip);
  if ($$props.removeChip === void 0 && $$bindings.removeChip && removeChip !== void 0)
    $$bindings.removeChip(removeChip);
  classesInvalid = inputValid === false ? invalid : "";
  classesBase = `${cBase} ${padding} ${rounded} ${$$props.class ?? ""} ${classesInvalid}`;
  classesChipWrapper = `${cChipWrapper} ${regionChipWrapper}`;
  classesChipList = `${cChipList} ${regionChipList}`;
  classesInput = `${cInputField} ${regionInput}`;
  chipValues = value?.map((val, i) => {
    if (chipValues[i]?.val === val)
      return chipValues[i];
    return { id: Math.random(), val };
  }) || [];
  $$unsubscribe_prefersReducedMotionStore();
  return `<div class="${[
    "input-chip " + escape(classesBase, true),
    $$restProps.disabled ? "opacity-50" : ""
  ].join(" ").trim()}"> <div class="h-0 overflow-hidden"><select${add_attribute("name", name, 0)} multiple ${required ? "required" : ""}${add_attribute("aria-label", label, 0)} tabindex="-1"${add_attribute("this", selectElement, 0)}>${each(value, (option) => {
    return `<option${add_attribute("value", option, 0)}>${escape(option)}</option>`;
  })}</select></div>  <div class="${"input-chip-wrapper " + escape(classesChipWrapper, true)}"> <form><input type="text"${add_attribute("placeholder", $$restProps.placeholder ?? "Enter values...", 0)} class="${"input-chip-field " + escape(classesInput, true)}" ${$$restProps.disabled ? "disabled" : ""}${add_attribute("value", input, 0)}></form>  ${chipValues.length ? `<div class="${"input-chip-list " + escape(classesChipList, true)}">${each(chipValues, ({ id, val }, i) => {
    return `<div><button type="button" class="${"chip " + escape(chips, true)}"><span>${escape(val)}</span> <span data-svelte-h="svelte-1p578dz">✕</span></button> </div>`;
  })}</div>` : ``}</div></div>`;
});

export { InputChip as I };
//# sourceMappingURL=InputChip-szkgPZLc.js.map
