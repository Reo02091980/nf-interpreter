//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <MCUboot_StartupPolicy.h>

#ifdef NF_FEATURE_HAS_MCUBOOT

void nf_mcuboot_startup_init(void)
{
    // Placeholder for startup policy initialization.
    // CLR image confirmation is performed later by nf_mcuboot_startup_ok(),
    // and deploy image confirmation is handled by nf_mcuboot_deploy_ok().
}

nf_mcuboot_error_t nf_mcuboot_deploy_ok(void)
{
    int swap_type;
    nf_mcuboot_error_t result;

    result = nf_mcuboot_image_state(NF_MCUBOOT_IMAGE_DEPLOY, &swap_type);
    if (result != NF_MCUBOOT_SUCCESS)
    {
        return result;
    }

    if (swap_type == BOOT_SWAP_TYPE_TEST)
    {
        result = nf_mcuboot_confirm_image(NF_MCUBOOT_IMAGE_DEPLOY);
        if (result != NF_MCUBOOT_SUCCESS)
        {
            return result;
        }
    }

    return NF_MCUBOOT_SUCCESS;
}

nf_mcuboot_error_t nf_mcuboot_deploy_failed(void)
{
    // No action required: keeping the deploy image unconfirmed causes MCUboot
    // to revert to the previous image on the next reboot.
    return NF_MCUBOOT_SUCCESS;
}

#endif // NF_FEATURE_HAS_MCUBOOT
