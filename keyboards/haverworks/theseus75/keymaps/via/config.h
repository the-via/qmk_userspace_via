// Copyright 2025 Alex Havermale (@haversnail), Moritz Plattner (@ebastler)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EECONFIG_USER_DATA_SIZE 4
#define WEAR_LEVELING_LOGICAL_SIZE 4096
#define WEAR_LEVELING_BACKING_SIZE WEAR_LEVELING_LOGICAL_SIZE*2
#define SPLIT_TRANSACTION_IDS_USER RPC_ID_INDICATOR_CONFIG
