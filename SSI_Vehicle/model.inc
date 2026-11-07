#if defined _INC_SSI_VEHICLE_MODEL
    #endinput
#endif
#define _INC_SSI_VEHICLE_MODEL

/*
Legal:
    Version: MPL 1.1

    The contents of this file are subject to the Mozilla Public License Version
    1.1 the "License"; you may not use this file except in compliance with
    the License. You may obtain a copy of the License at
    http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS IS" basis,
    WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
    for the specific language governing rights and limitations under the
    License.

    The Original Code is the YSI framework.

    The Initial Developer of the Original Code is Alex "Y_Less" Cole.
    Portions created by the Initial Developer are Copyright (c) 2022
    the Initial Developer. All Rights Reserved.

    Portions created by imshooter are Copyright (c) 2026 imshooter.

Modifications:
    2026-11, imshooter: the model data of y_vehicledata moved into this
    include, without the flags of where a vehicle is found on the map, with
    categories and flags as tagged enums and a lookup of a model by its name.
*/

#include <open.mp>
#include <SSI\dictionary>
#include <SSI\string>
#include <SSI_Vehicle\components>
#include <SSI\hooks>

/**
 * Name, category and flags of every vehicle model, read by model id.
 *
 * A model has one category, such as Off Road for a Sanchez, and any number of
 * flags: a Seasparrow is a helicopter, floats and is armed. Pushbikes and train
 * carriages have flags of their own, since the game treats them as bikes and
 * cars.
 *
 * A model is also found by its name, in any case. Of two models with one name,
 * as the Boxville, the first is found.
 *
 * The data is from y_vehicledata of YSI, so this file stays under the Mozilla
 * Public License 1.1, as its notice at the top says.
 */

/**
 * # Header
 */

#if !defined MAX_VEHICLE_MODEL_NAME
    #define MAX_VEHICLE_MODEL_NAME (32)
#endif

enum VEHICLE_CATEGORY {
    VEHICLE_CATEGORY_NONE,

    VEHICLE_CATEGORY_SALOON,
    VEHICLE_CATEGORY_SPORT,
    VEHICLE_CATEGORY_OFFROAD,
    VEHICLE_CATEGORY_STATION,
    VEHICLE_CATEGORY_CONVERTIBLE,
    VEHICLE_CATEGORY_LOWRIDER,
    VEHICLE_CATEGORY_INDUSTRIAL,
    VEHICLE_CATEGORY_PUBLIC,
    VEHICLE_CATEGORY_UNIQUE,
    VEHICLE_CATEGORY_BIKE,
    VEHICLE_CATEGORY_BOAT,
    VEHICLE_CATEGORY_AIRPLANE,
    VEHICLE_CATEGORY_HELICOPTER,
    VEHICLE_CATEGORY_TRAILER,
    VEHICLE_CATEGORY_RC
};

enum VEHICLE_FLAGS: (<<= 1) {
    VEHICLE_NONE = 0,

    VEHICLE_CAR = 1,
    VEHICLE_BIKE,
    VEHICLE_BOAT,
    VEHICLE_PLANE,
    VEHICLE_HELICOPTER,
    VEHICLE_TRAIN,
    VEHICLE_PUSHBIKE,

    VEHICLE_TRUCK,
    VEHICLE_VAN,
    VEHICLE_TANK,
    VEHICLE_ONWATER,
    VEHICLE_MANUAL,

    VEHICLE_POLICE,
    VEHICLE_SWAT,
    VEHICLE_FBI,
    VEHICLE_MILITARY,
    VEHICLE_AMBULANCE,
    VEHICLE_FIRE,
    VEHICLE_TAXI,
    VEHICLE_COASTGUARD,
    VEHICLE_TRANSPORT,

    VEHICLE_WEAPONISED,
    VEHICLE_ARMED
};

#define VEHICLE_NOT_GROUND (VEHICLE_PLANE | VEHICLE_HELICOPTER | VEHICLE_BOAT | VEHICLE_ONWATER | VEHICLE_TRAIN)


/**
 * Flags of a row of `gVehicleModelData`, written without the prefix, such as
 * VEHICLE<CAR | POLICE | NONE | NONE>.
 */
#define VEHICLE<%0> VEHICLE_NONE| %0| END|
#define VEHICLE_NONE|%0\32;%1| VEHICLE_%1|VEHICLE_NONE|
#define VEHICLE_END|VEHICLE_NONE| VEHICLE_NONE

static enum E_VEHICLE_MODEL_DATA {
    E_VEHICLE_MODEL_NAME[(MAX_VEHICLE_MODEL_NAME + 1) char],
    VEHICLE_CATEGORY:E_VEHICLE_MODEL_CATEGORY,
    VEHICLE_FLAGS:E_VEHICLE_MODEL_FLAGS
};

static
    Dictionary:VehicleModelByName<MAX_VEHICLE_MODELS, MAX_VEHICLE_MODEL_NAME>
;

static stock const gVehicleModelData[][E_VEHICLE_MODEL_DATA] = {
    { !"Landstalker"                 , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 400
    { !"Bravura"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 401
    { !"Buffalo"                     , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 402
    { !"Linerunner"                  , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 403
    { !"Perennial"                   , VEHICLE_CATEGORY_STATION    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 404
    { !"Sentinel"                    , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 405
    { !"Dumper"                      , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 406
    { !"Firetruck"                   , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRUCK      | WEAPONISED | FIRE       | NONE>  }, // 407
    { !"Trashmaster"                 , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 408
    { !"Stretch"                     , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 409
    { !"Manana"                      , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 410
    { !"Infernus"                    , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 411
    { !"Voodoo"                      , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 412
    { !"Pony"                        , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 413
    { !"Mule"                        , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 414
    { !"Cheetah"                     , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 415
    { !"Ambulance"                   , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<VAN        | AMBULANCE  | NONE       | NONE>  }, // 416
    { !"Leviathan"                   , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 417
    { !"Moonbeam"                    , VEHICLE_CATEGORY_STATION    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 418
    { !"Esperanto"                   , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 419
    { !"Taxi"                        , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | TAXI       | NONE       | NONE>  }, // 420
    { !"Washington"                  , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 421
    { !"Bobcat"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 422
    { !"Mr. Whoopee"                 , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 423
    { !"BF Injection"                , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 424
    { !"Hunter"                      , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | WEAPONISED | MILITARY   | ARMED> }, // 425
    { !"Premier"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 426
    { !"Enforcer"                    , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRUCK      | POLICE     | NONE       | NONE>  }, // 427
    { !"Securicar"                   , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 428
    { !"Banshee"                     , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 429
    { !"Predator"                    , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | WEAPONISED | POLICE     | ARMED> }, // 430
    { !"Bus"                         , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRANSPORT  | NONE       | NONE       | NONE>  }, // 431
    { !"Rhino"                       , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<WEAPONISED | MILITARY   | TANK       | ARMED> }, // 432
    { !"Barracks"                    , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRUCK      | MILITARY   | NONE       | NONE>  }, // 433
    { !"Hotknife"                    , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 434
    { !"Article Trailer"             , VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 435
    { !"Previon"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 436
    { !"Coach"                       , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRANSPORT  | NONE       | NONE       | NONE>  }, // 437
    { !"Cabbie"                      , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | TAXI       | NONE       | NONE>  }, // 438
    { !"Stallion"                    , VEHICLE_CATEGORY_CONVERTIBLE, VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 439
    { !"Rumpo"                       , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 440
    { !"RC Bandit"                   , VEHICLE_CATEGORY_RC         , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 441
    { !"Romero"                      , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 442
    { !"Packer"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 443
    { !"Monster"                     , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 444
    { !"Admiral"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 445
    { !"Squallo"                     , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 446
    { !"Seasparrow"                  , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<BOAT       | HELICOPTER | ONWATER    | ARMED> }, // 447
    { !"Pizzaboy"                    , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 448
    { !"Tram"                        , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRAIN      | NONE       | NONE       | NONE>  }, // 449
    { !"Article Trailer 2"           , VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 450
    { !"Turismo"                     , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 451
    { !"Speeder"                     , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 452
    { !"Reefer"                      , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 453
    { !"Tropic"                      , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 454
    { !"Flatbed"                     , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 455
    { !"Yankee"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 456
    { !"Caddy"                       , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 457
    { !"Solair"                      , VEHICLE_CATEGORY_STATION    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 458
    { !"Topfun Van (Berkley's RC)"   , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 459
    { !"Skimmer"                     , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<BOAT       | PLANE      | ONWATER    | NONE>  }, // 460
    { !"PCJ-600"                     , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 461
    { !"Faggio"                      , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 462
    { !"Freeway"                     , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 463
    { !"RC Baron"                    , VEHICLE_CATEGORY_RC         , VEHICLE<PLANE      | ARMED      | NONE       | NONE>  }, // 464
    { !"RC Raider"                   , VEHICLE_CATEGORY_RC         , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 465
    { !"Glendale"                    , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 466
    { !"Oceanic"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 467
    { !"Sanchez"                     , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 468
    { !"Sparrow"                     , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 469
    { !"Patriot"                     , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | MILITARY   | NONE       | NONE>  }, // 470
    { !"Quad"                        , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | CAR        | NONE       | NONE>  }, // 471
    { !"Coastguard"                  , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | COASTGUARD | NONE       | NONE>  }, // 472
    { !"Dinghy"                      , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 473
    { !"Hermes"                      , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 474
    { !"Sabre"                       , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 475
    { !"Rustler"                     , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | ARMED      | NONE       | NONE>  }, // 476
    { !"ZR-350"                      , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 477
    { !"Walton"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 478
    { !"Regina"                      , VEHICLE_CATEGORY_STATION    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 479
    { !"Comet"                       , VEHICLE_CATEGORY_CONVERTIBLE, VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 480
    { !"BMX"                         , VEHICLE_CATEGORY_BIKE       , VEHICLE<MANUAL     | PUSHBIKE   | NONE       | NONE>  }, // 481
    { !"Burrito"                     , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 482
    { !"Camper"                      , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRANSPORT  | NONE       | NONE       | NONE>  }, // 483
    { !"Marquis"                     , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 484
    { !"Baggage"                     , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 485
    { !"Dozer"                       , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 486
    { !"Maverick"                    , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 487
    { !"SAN News Maverick"           , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 488
    { !"Rancher"                     , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 489
    { !"FBI Rancher"                 , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | FBI        | NONE       | NONE>  }, // 490
    { !"Virgo"                       , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 491
    { !"Greenwood"                   , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 492
    { !"Jetmax"                      , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 493
    { !"Hotring Racer"               , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 494
    { !"Sandking"                    , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 495
    { !"Blista Compact"              , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 496
    { !"Police Maverick"             , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | POLICE     | NONE       | NONE>  }, // 497
    { !"Boxville"                    , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 498
    { !"Benson"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 499
    { !"Mesa"                        , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 500
    { !"RC Goblin"                   , VEHICLE_CATEGORY_RC         , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 501
    { !"Hotring Racer A"             , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 502
    { !"Hotring Racer B"             , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 503
    { !"Bloodring Banger"            , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 504
    { !"Rancher Lure"                , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 505
    { !"Super GT"                    , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 506
    { !"Elegant"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 507
    { !"Journey"                     , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRANSPORT  | NONE       | NONE       | NONE>  }, // 508
    { !"Bike"                        , VEHICLE_CATEGORY_BIKE       , VEHICLE<MANUAL     | PUSHBIKE   | NONE       | NONE>  }, // 509
    { !"Mountain Bike"               , VEHICLE_CATEGORY_BIKE       , VEHICLE<MANUAL     | PUSHBIKE   | NONE       | NONE>  }, // 510
    { !"Beagle"                      , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 511
    { !"Cropduster"                  , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 512
    { !"Stuntplane"                  , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 513
    { !"Tanker"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 514
    { !"Roadtrain"                   , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 515
    { !"Nebula"                      , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 516
    { !"Majestic"                    , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 517
    { !"Buccaneer"                   , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 518
    { !"Shamal"                      , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 519
    { !"Hydra"                       , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | WEAPONISED | MILITARY   | ARMED> }, // 520
    { !"FCR-900"                     , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 521
    { !"NRG-500"                     , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 522
    { !"HPV1000"                     , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<BIKE       | POLICE     | NONE       | NONE>  }, // 523
    { !"Cement Truck"                , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 524
    { !"Towtruck"                    , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 525
    { !"Fortune"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 526
    { !"Cadrona"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 527
    { !"FBI Truck"                   , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRUCK      | FBI        | NONE       | NONE>  }, // 528
    { !"Willard"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 529
    { !"Forklift"                    , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 530
    { !"Tractor"                     , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 531
    { !"Combine Harvester"           , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 532
    { !"Feltzer"                     , VEHICLE_CATEGORY_CONVERTIBLE, VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 533
    { !"Remington"                   , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 534
    { !"Slamvan"                     , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 535
    { !"Blade"                       , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 536
    { !"Freight (Train)"             , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRAIN      | NONE       | NONE       | NONE>  }, // 537
    { !"Brownstreak (Train)"         , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<TRAIN      | NONE       | NONE       | NONE>  }, // 538
    { !"Vortex"                      , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<BOAT       | CAR        | ONWATER    | NONE>  }, // 539
    { !"Vincent"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 540
    { !"Bullet"                      , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 541
    { !"Clover"                      , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 542
    { !"Sadler"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 543
    { !"Firetruck LA"                , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRUCK      | WEAPONISED | FIRE       | NONE>  }, // 544
    { !"Hustler"                     , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 545
    { !"Intruder"                    , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 546
    { !"Primo"                       , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 547
    { !"Cargobob"                    , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 548
    { !"Tampa"                       , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 549
    { !"Sunrise"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 550
    { !"Merit"                       , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 551
    { !"Utility Van"                 , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 552
    { !"Nevada"                      , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 553
    { !"Yosemite"                    , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 554
    { !"Windsor"                     , VEHICLE_CATEGORY_CONVERTIBLE, VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 555
    { !"Monster A"                   , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 556
    { !"Monster B"                   , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 557
    { !"Uranus"                      , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 558
    { !"Jester"                      , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 559
    { !"Sultan"                      , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 560
    { !"Stratum"                     , VEHICLE_CATEGORY_STATION    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 561
    { !"Elegy"                       , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 562
    { !"Raindance"                   , VEHICLE_CATEGORY_HELICOPTER , VEHICLE<HELICOPTER | NONE       | NONE       | NONE>  }, // 563
    { !"RC Tiger"                    , VEHICLE_CATEGORY_RC         , VEHICLE<WEAPONISED | TANK       | NONE       | NONE>  }, // 564
    { !"Flash"                       , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 565
    { !"Tahoma"                      , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 566
    { !"Savanna"                     , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 567
    { !"Bandito"                     , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 568
    { !"Freight Flat Trailer (Train)", VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRAIN      | NONE       | NONE       | NONE>  }, // 569
    { !"Streak Trailer (Train)"      , VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRAIN      | NONE       | NONE       | NONE>  }, // 570
    { !"Kart"                        , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 571
    { !"Mower"                       , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 572
    { !"Dune"                        , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 573
    { !"Sweeper"                     , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 574
    { !"Broadway"                    , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 575
    { !"Tornado"                     , VEHICLE_CATEGORY_LOWRIDER   , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 576
    { !"AT400"                       , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 577
    { !"DFT-30"                      , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 578
    { !"Huntley"                     , VEHICLE_CATEGORY_OFFROAD    , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 579
    { !"Stafford"                    , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 580
    { !"BF-400"                      , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 581
    { !"Newsvan"                     , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 582
    { !"Tug"                         , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 583
    { !"Petrol Trailer"              , VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 584
    { !"Emperor"                     , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 585
    { !"Wayfarer"                    , VEHICLE_CATEGORY_BIKE       , VEHICLE<BIKE       | NONE       | NONE       | NONE>  }, // 586
    { !"Euros"                       , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 587
    { !"Hotdog"                      , VEHICLE_CATEGORY_UNIQUE     , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 588
    { !"Club"                        , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 589
    { !"Freight Box Trailer (Train)" , VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRAIN      | NONE       | NONE       | NONE>  }, // 590
    { !"Article Trailer 3"           , VEHICLE_CATEGORY_TRAILER    , VEHICLE<TRUCK      | NONE       | NONE       | NONE>  }, // 591
    { !"Andromada"                   , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 592
    { !"Dodo"                        , VEHICLE_CATEGORY_AIRPLANE   , VEHICLE<PLANE      | NONE       | NONE       | NONE>  }, // 593
    { !"RC Cam"                      , VEHICLE_CATEGORY_RC         , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 594
    { !"Launch"                      , VEHICLE_CATEGORY_BOAT       , VEHICLE<BOAT       | NONE       | NONE       | NONE>  }, // 595
    { !"Police Car (LSPD)"           , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | POLICE     | NONE       | NONE>  }, // 596
    { !"Police Car (SFPD)"           , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | POLICE     | NONE       | NONE>  }, // 597
    { !"Police Car (LVPD)"           , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | POLICE     | NONE       | NONE>  }, // 598
    { !"Police Ranger"               , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<CAR        | POLICE     | NONE       | NONE>  }, // 599
    { !"Picador"                     , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 600
    { !"S.W.A.T."                    , VEHICLE_CATEGORY_PUBLIC     , VEHICLE<TRUCK      | WEAPONISED | POLICE     | SWAT>  }, // 601
    { !"Alpha"                       , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 602
    { !"Phoenix"                     , VEHICLE_CATEGORY_SPORT      , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 603
    { !"Glendale Shit"               , VEHICLE_CATEGORY_SALOON     , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 604
    { !"Sadler Shit"                 , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<CAR        | NONE       | NONE       | NONE>  }, // 605
    { !"Baggage Trailer A"           , VEHICLE_CATEGORY_TRAILER    , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 606
    { !"Baggage Trailer B"           , VEHICLE_CATEGORY_TRAILER    , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 607
    { !"Tug Stairs Trailer"          , VEHICLE_CATEGORY_TRAILER    , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 608
    { !"Boxville"                    , VEHICLE_CATEGORY_INDUSTRIAL , VEHICLE<VAN        | NONE       | NONE       | NONE>  }, // 609
    { !"Farm Trailer"                , VEHICLE_CATEGORY_TRAILER    , VEHICLE<NONE       | NONE       | NONE       | NONE>  }, // 610
    { !"Utility Trailer"             , VEHICLE_CATEGORY_TRAILER    , VEHICLE<NONE       | NONE       | NONE       | NONE>  } // 611
};

/**
 * # Functions
 */

/**
 * @brief      The flags of a vehicle model.
 *
 * @param      modelid  Model to read.
 *
 * @return     - its flags
 *             - `VEHICLE_NONE` `modelid` is not a vehicle model
 */
forward VEHICLE_FLAGS:GetVehicleModelFlags(modelid);

/**
 * @brief      Whether a vehicle model has all of some flags.
 *
 * `VEHICLE_POLICE | VEHICLE_CAR` finds a police car and not a police boat.
 *
 * @param      modelid  Model to check.
 * @param      flags    Flags to look for.
 *
 * @return     - `true` it has all of them
 *             - `false` it lacks one
 */
forward bool:IsVehicleModelFlagged(modelid, VEHICLE_FLAGS:flags);

/**
 * @brief      The category of a vehicle model.
 *
 * @param      modelid  Model to read.
 *
 * @return     - the category
 *             - `VEHICLE_CATEGORY_NONE` `modelid` is not a vehicle model
 */
forward VEHICLE_CATEGORY:GetVehicleModelCategory(modelid);

/**
 * @brief      The name of a vehicle model.
 *
 * @param      modelid  Model to read.
 * @param      output   Reads back the name, or is emptied on failure.
 * @param      size     Size of `output`.
 *
 * @return     - `true` the name was written
 *             - `false` `modelid` is not a vehicle model
 */
forward bool:GetVehicleModelName(modelid, output[], size = sizeof (output));

/**
 * @brief      The vehicle model with a name, in any case.
 *
 * @param      name  Name to find, such as "infernus".
 *
 * @return     - the model
 *             - `0` no model has that name
 */
forward GetVehicleModelByName(const name[]);

/**
 * @brief      The flags of a vehicle.
 *
 * @param      vehicleid  Vehicle to read.
 *
 * @return     - its flags
 *             - `VEHICLE_NONE` `vehicleid` is not a valid vehicle
 */
forward VEHICLE_FLAGS:GetVehicleFlags(vehicleid);

/**
 * @brief      Whether a vehicle has all of some flags.
 *
 * @param      vehicleid  Vehicle to check.
 * @param      flags      Flags to look for.
 *
 * @return     - `true` it has all of them
 *             - `false` it lacks one
 */
forward bool:IsVehicleFlagged(vehicleid, VEHICLE_FLAGS:flags);

/**
 * @brief      The category of a vehicle.
 *
 * @param      vehicleid  Vehicle to read.
 *
 * @return     - the category
 *             - `VEHICLE_CATEGORY_NONE` `vehicleid` is not a valid vehicle
 */
forward VEHICLE_CATEGORY:GetVehicleCategory(vehicleid);

/**
 * @brief      Whether a model drives on roads, as a garage takes.
 *
 * @param      modelid  Model to check.
 *
 * @return     - `true` it is a car or a motorbike
 *             - `false` it is not
 */
forward bool:IsVehicleModelGround(modelid);

/**
 * @brief      Whether a model flies, as a hangar takes.
 *
 * @param      modelid  Model to check.
 *
 * @return     - `true` it is a plane or a helicopter
 *             - `false` it is not
 */
forward bool:IsVehicleModelAir(modelid);

/**
 * @brief      Whether a model goes on water, as a marina takes.
 *
 * A Seasparrow is both air and water.
 *
 * @param      modelid  Model to check.
 *
 * @return     - `true` it goes on water
 *             - `false` it does not
 */
forward bool:IsVehicleModelWater(modelid);

/**
 * @brief      Whether a model can be owned.
 *
 * Trailers, train carriages, pushbikes and remote control toys cannot.
 *
 * @param      modelid  Model to check.
 *
 * @return     - `true` it can be owned
 *             - `false` it cannot
 */
forward bool:IsVehicleModelOwnable(modelid);

/**
 * # Vehicle Model
 */

stock VEHICLE_FLAGS:GetVehicleModelFlags(modelid) {
    if (!IsValidVehicleModel(modelid)) {
        return VEHICLE_NONE;
    }

    return gVehicleModelData[modelid - MIN_VEHICLE_MODEL_ID][E_VEHICLE_MODEL_FLAGS];
}

stock bool:IsVehicleModelFlagged(modelid, VEHICLE_FLAGS:flags) {
    return ((GetVehicleModelFlags(modelid) & flags) == flags);
}

stock VEHICLE_CATEGORY:GetVehicleModelCategory(modelid) {
    if (!IsValidVehicleModel(modelid)) {
        return VEHICLE_CATEGORY_NONE;
    }

    return gVehicleModelData[modelid - MIN_VEHICLE_MODEL_ID][E_VEHICLE_MODEL_CATEGORY];
}

stock bool:GetVehicleModelName(modelid, output[], size = sizeof (output)) {
    output[0] = EOS;

    if (!IsValidVehicleModel(modelid)) {
        return false;
    }

    strunpack(output, gVehicleModelData[modelid - MIN_VEHICLE_MODEL_ID][E_VEHICLE_MODEL_NAME], size);

    return true;
}

stock GetVehicleModelByName(const name[]) {
    new
        lower[MAX_VEHICLE_MODEL_NAME + 1],
        modelid
    ;

    strcat(lower, name);

    String_ToLower(lower);

    if (!Dictionary_Get(VehicleModelByName<>, lower, modelid)) {
        return 0;
    }

    return modelid;
}

stock VEHICLE_FLAGS:GetVehicleFlags(vehicleid) {
    return GetVehicleModelFlags(GetVehicleModel(vehicleid));
}

stock bool:IsVehicleFlagged(vehicleid, VEHICLE_FLAGS:flags) {
    return IsVehicleModelFlagged(GetVehicleModel(vehicleid), flags);
}

stock VEHICLE_CATEGORY:GetVehicleCategory(vehicleid) {
    return GetVehicleModelCategory(GetVehicleModel(vehicleid));
}

stock bool:IsVehicleModelGround(modelid) {
    if (!IsValidVehicleModel(modelid)) {
        return false;
    }

    return ((GetVehicleModelFlags(modelid) & VEHICLE_NOT_GROUND) == VEHICLE_NONE);
}

stock bool:IsVehicleModelAir(modelid) {
    return ((GetVehicleModelFlags(modelid) & (VEHICLE_PLANE | VEHICLE_HELICOPTER)) != VEHICLE_NONE);
}

stock bool:IsVehicleModelWater(modelid) {
    return ((GetVehicleModelFlags(modelid) & (VEHICLE_BOAT | VEHICLE_ONWATER)) != VEHICLE_NONE);
}

stock bool:IsVehicleModelOwnable(modelid) {
    new const
        VEHICLE_FLAGS:flags = GetVehicleModelFlags(modelid)
    ;

    if (flags & (VEHICLE_TRAIN | VEHICLE_PUSHBIKE)) {
        return false;
    }

    return ((flags & (VEHICLE_CAR | VEHICLE_BIKE | VEHICLE_BOAT | VEHICLE_PLANE | VEHICLE_HELICOPTER)) != VEHICLE_NONE);
}

/**
 * # Calls
 */

hook OnGameModeInit() {
    new
        name[MAX_VEHICLE_MODEL_NAME + 1]
    ;

    for (new modelid = MIN_VEHICLE_MODEL_ID; modelid <= MAX_VEHICLE_MODEL_ID; ++modelid) {
        GetVehicleModelName(modelid, name);

        String_ToLower(name);

        if (!Dictionary_Contains(VehicleModelByName<>, name)) {
            Dictionary_Set(VehicleModelByName<>, name, modelid);
        }
    }

    return 1;
}
