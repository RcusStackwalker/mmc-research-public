const uint16_t *const flash_injector_scaling_multiu16[MODE_COUNT] = {
	&flash_injector_scaling,
	&flash_alternative_injector_scaling,
	&live_injector_scaling,
};

const void *const flash_maf_additive_scaling_2dmap8[MODE_COUNT] = {
	&flash_maf_additive_scaling_2dmap8,
	&flash_alternative_maf_additive_scaling_2dmap8,
	&live_maf_additive_scaling_2dmap8,
};

void update_alt_vars()
{
	injector_scaling = multiptru16a_dereferenced(flash_injector_scaling_multiu16);
	maf_additive_scaling_map_pointer = multiptr(flash_maf_additive_scaling_2dmap8);
}
