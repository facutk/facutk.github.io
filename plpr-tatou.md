## PLPR TATOU ##

`ZBPRISDV01_PB1_XP93A` processes file from PLPR.
Updates Purchase Orders and creates Idocs for Delivery, Invoice and Transfer

### Process Description ###

    Read file ZBPR_PL093A_IN_01 -> Header, Invoice, Package
    if Invoice-KUNAG in TVARV-ZBPR_PLPR_STOCK_CLIENTS:
        Stock Order
    else:
        Urgent Order
    
    for each Urgent Order:
        Update Purchase Order
        Release Purchase Order
        Create Idoc Delivery
        Create Idoc Invoice

    for each Stock Order:
        Update Purchase Order
        Release Purchase Order
        Close Delivered Purchase Order positions
        Copy Closed Purchase Orders from BR00 to BR17
        Create Idoc Delivery
        Create Idoc Invoice
        Create Idoc Transfer

    Show log

### XP0093 File ###
Abridged format (full specification available in SFD)

- Type 1: `Invoice` Line
    - VBELN : `Invoice` number
    - POSNR : `Invoice` position
    - KUNAG: `Contract client` (determines priority)
    - LDS : `EBELN`/`EBELP` (from Tatou)
    - FKDAT : `Invoice` date
    - MATNR : `Delivered material`
    - LFIMG : `Delivered quantity`
    - MATWA : `Ordered material`
    - FKIMG : `Ordered quantity`
- Type 2: `Package` Line
    - VBELN : `Invoice` number
    - POSNR : `Invoice` position
    - QTE_COLIS : Quantity in the `Package`
    - NUM_COLIS : `Package` number
- Type 3: `Invoice` Header
    - VBELN : `Invoice` number

#### Rule: Package Consistency ####

> An `Invoice` can have many `Packages`. A `package` cannot be in different  `invoices`. If this rule is broken, the file must not be processed. Log  must describe `invoices`/`packages` involved.

#### Rule: No reprocess invoices ####

> Existing invoices must not be reprocessed. RBKP table keeps track of processed invoices.

### Purchase Order Update Rules ###

1. *Invoice Control*
	
    If `Goods Received-Based Invoice Verification` is marked, unmark it.

2. *Equal material, equal quantity*
  - `delivered material` == `ordered material`
  - `delivered quantity` == `ordered quantity`
  
    Position fully delivered. Mark `Delivery Completed`.

3. *Different material, equal quantity*
  - `delivered material` <> `ordered material`
  - `delivered quantity` == `ordered quantity`

    Position fully delivered. Mark `Delivery Completed`.
    
    Crete new position with `delivered material`.
    Mark `Delivery Completed`.

4. *Equal material, less quantity*

  - `delivered material` = `ordered material`
  - `delivered quantity` < `ordered quantity`

    Update position quantity with `delivered quantity`.
    
    Create new position with `remaining quantity` and `Purchase Requisition`.

5. *Equal material, more quantity*

  - `delivered material` = `ordered material`
  - `delivered quantity` > `ordered quantity`

    Update position quantity with `delivered quantity`. 

6. *Different material, more quantity*

  - `delivered material` <> `ordered material`
  - `delivered quantity`  > `ordered quantity`

    Crete new position with `delivered material` and `delivered quantity`.
 
    Update existing position quantity with `ordered quantity` - `delivered quantity`.

    If existing position `quantity` is `0`: mark `Delivery Completed`.

7. *Different material, less quantity*

  - `delivered material` <> `ordered material`
  - `delivered quantity` <  `ordered quantity`

    Update existing position quantity with `ordered quantity` - `delivered quantity`.
    
    Crete new position with `delivered material` and `delivered quantity`.
 
    In the `Purchase Requisition`: Create new position with `delivered material` and `delivered quantity`.


### Idoc ZBPR_DELVRY05 ###

- E1EDL20
    - TRAID: `ws_final3-vbeln`
    - LIFEX: `ws_final3-vbeln`
- E1EDT13
    - QUALF: `007`
    - NTANF: `ws_final1-fkdat` + delay Urgent (`TVARV-ZBPR_PLPR_URGENT`) or delay Stock (`TVARV-ZBPR_PLPR_STOCK`) + Calenday day adjust
- E1EDL24
    - POSNR: ws_final1-posnr
    - MATNR: ws_final1-matnr
    - LFIMG: ws_final1-lfimg
    - VRKME: MVKE_VRKME
- E1EDL41
    - QUALI: `001`
    - BSTNR: `ws_final1-LDS[ EBELN ]`
    - POSEX: `ws_final1-LDS[ EBELP ]`
- E1EDL37
    - EXIDV: `ws_final2-num_colis`
    - `VHILM_KU`: read `ZARTEMBALLESAP` from `ZBRPARTEMBALLAGE` where `ZARTEMBALLE` is `ws_final2-ZARTEMBALLE`
- E1EDL44
    - POSNR: `ws_final2-posnr`
    - EXIDV: `ws_final2-num_colis`
    - VEMNG: `ws_final2-qte_colis`
    - VEMEH: ``
    - MATNR: `ws_final2-lf_matnr`     
    - KDMAT: `ws_final2-lf_matnr`


### Idoc ZBPR_INVOIC01 ###

- E1EDK01
    - NTGEW: `MARA_NTGEW` Poids net unitaire de la pièce
    - BRGEW: `MARA_BRGEW` Poids brut unitaire de la pièce
    - CURCY: `USD` 
- E1EDKA1 (2 segments)
    - PARVW: `LF`
    - PARTN: `VENDOR` from `BAPI_PO_GETDETAIL1` with PO = `EBELN`
- E1EDK02
    - QUALF: `009`
    - BELNR: `ws_final3-vbeln` 
- E1EDK03
    - IDDAT: `012`
    - DATUM: `ws_final1-fkdat`
- E1EDK04
    - MWSKZ: `VAT`	
- E1EDP01
    - POSEX: `ws_final1-posnr`
    - MENGE: `ws_final1-lfimg`
- E1EDP02 
    - QUALF: `001`
    - BELNR: `ws_final1-lds`, first from split at '/' : `EBELN`
    - ZEILE: `ws_final1-lds`, second from split at '/' : `EBELP`
- E1EDP19
    - QUALF: `001`
    - IDTNR: `ws_final1-matnr`
- E1EDP26
    - QUALF: `0`
    - BETRG: `ws_final1-net_amount` / 100
- E1EDS01
    - SUMID: `010`
    - SUMME: `ws_final3-netwr` / 100






### Idoc ZBPR_ORDERS02 ###
- E1EDK01
    - ACTION : 000 001
    - BSART : ZUB
    - BELNR : Numéro du document Généré en auto par SAP
- E1EDK14
    - QUALF : 005
    - ORGID : BR17
    - QUALF : 009
    - ORGID : ZPP
    - QUALF : 014
    - ORGID : MS40
- E1EDK03
    - IDDAT : 022
    - DATUM : run date
    - IDDAT : 001
    - DATUM : Date in the file + stock delay
- E1EDKA1
    - PARVW: AG/LF
    - IHREZ: COLIS
    - PARTN: BR17
- E1EDP01
    - POSEX: num poste PO BR17
    - ACTION: 001
    - PSTYP: 7
    - MENGE: Quantity
    - MENEE: Quantity unit
    - PMENE: Billing Unit
    - VPREI: Net price
    - PEINH: Base Price
- E1EDP19
    - QUALF: 002
    - IDTNR: Article number
- E1EDPA1
    - PARVW: WE
    - PARTN: BR00
